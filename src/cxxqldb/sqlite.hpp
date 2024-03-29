#pragma once
#include "sqlite/injection.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <functional>
#include <sqlite3.h>
#include <avalon/mp/identity.hpp>
#include <avalon/defer.hpp>
#include <cxxql.hpp>

namespace cxxqldb::sqlite {

template<class ResultElem>
struct dataset_range {
  using value_type = ResultElem;
  template<class T>
  using tid = avalon::mp::identity<T>;

  dataset_range(sqlite3_stmt* stmt)
  : stmt_(stmt)
  {}

  dataset_range() = default;
  
  value_type read() const{
    ResultElem res_elem;
    set_re(res_elem, std::make_integer_sequence<std::size_t, value_type::col_num>{});
    return res_elem;
  }
  void next() {}
  bool has_next() const {
    auto res = sqlite3_step(stmt_) != SQLITE_DONE;
    if(!res) {
      sqlite3_finalize(stmt_);
    }
    return res;
  }
  
private:
  template<std::size_t i>
  auto stmt_col_v() const {
    using cxxqltype = typename value_type::template col_cxxqltype<i>;
    auto col_func = stmt_col_func(tid<cxxqltype>{});
    auto col_v = col_func(stmt_, i);
    if constexpr(std::is_same_v<decltype(col_v), const unsigned char*>) {
      return (const char*)col_v;
    } else {
      return col_v;
    }
  }

  template<std::size_t n>
  auto stmt_col_func(tid<cxxql::varchar<n>> t)  const { return sqlite3_column_text;     }
  auto stmt_col_func(tid<cxxql::blob> t)        const { return sqlite3_column_blob;     }
  auto stmt_col_func(tid<cxxql::integer> t)     const { return sqlite3_column_int;      }
  auto stmt_col_func(tid<cxxql::smallint> t)    const { return sqlite3_column_int;      }
  auto stmt_col_func(tid<cxxql::bigint> t)      const { return sqlite3_column_int64;    } // TODO: not sure
  auto stmt_col_func(tid<cxxql::real> t)        const { return sqlite3_column_double;   }

  template<class Int, Int... i>
  void set_re(value_type& re, std::integer_sequence<Int, i...> is) const {
    re.set(stmt_col_v<i>()...);
  }

  sqlite3_stmt* stmt_ {nullptr};
};

template<class Config>
struct db : public cxxql::db<db<Config>> {
  db(Config&& config) {
    sqlite3_open(config.file_path, &db_);
    if( db_ == nullptr ) {
      throw std::runtime_error("sqlite db open failed");
    }
  }
  ~db() {
    sqlite3_close(db_);
  }
  template<class ResultElem>
  auto select(const std::string& sql) {
    if(dbglog) {
      dbglog(fmt::format("exec: {}", sql));
    }
    sqlite3_stmt* stmt;
    auto ec = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr);
    if(ec != SQLITE_OK) {
      throw std::runtime_error("sqlite db select failed");
    }
    dataset_range<ResultElem> dr(stmt);
    return dr;
  }

  auto exec(const std::string& sql) {
    if(dbglog) {
      dbglog(fmt::format("exec: {}", sql));
    }
    char* err_msg = nullptr;
    auto rc = sqlite3_exec(db_, sql.c_str(), 0, 0, &err_msg);
    if(rc != SQLITE_OK) {
      auto holder = avalon::defer([err_msg](){
        sqlite3_free(err_msg);
      });
      throw std::runtime_error(err_msg);
    }
    return rc;
  }
  std::function<void(const std::string&)> dbglog;
private:
  sqlite3* db_;
};
template<class Config>
auto make_db(Config&& config) {
  return db<Config>{std::forward<Config>(config)};
}
}