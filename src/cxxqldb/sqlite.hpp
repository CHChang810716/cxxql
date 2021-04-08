#pragma once
#include <sqlite3.h>
#include <stdexcept>
#include <cxxql/type.hpp>
#include <utility>

namespace cxxqldb::sqlite {

template<class MakeResultElem>
struct dataset_range {
  using result_elem_t = decltype(MakeResultElem{}());
  template<class T>
  using tid = avalon::identity<T>;
  result_elem_t read() const{
    auto res_elem = make_result_elem_();
    set_re(result_elem, std::make_integer_sequence<std::size_t, result_elem_t::col_num>);
    return res_elem;
  }
  void next() {}
  bool has_next() const {
    return sqlite3_step(stmt) != SQLITE_DONE;
  }
private:
  template<std::size_t i>
  auto stmt_col_v() {
    using cxxqltype = typename result_elem_t::col_cxxqltype<i>;
    auto col_func = stmt_col_func(tid<cxxqltype>{});
    return col_func(stmt_, i);
  }

  template<std::size_t n>
  auto stmt_col_func(tid<cxxql::varchar<n>> t)  { return sqlite3_column_text;     }
  auto stmt_col_func(tid<cxxql::blob> t)        { return sqlite3_column_blob;     }
  auto stmt_col_func(tid<cxxql::integer> t)     { return sqlite3_column_int;      }
  auto stmt_col_func(tid<cxxql::smallint> t)    { return sqlite3_column_int;      }
  auto stmt_col_func(tid<cxxql::bigint> t)      { return sqlite3_column_int64;    } // TODO: not sure
  auto stmt_col_func(tid<cxxql::real> t)        { return sqlite3_column_double;   }

  template<class Int, Int... i>
  void set_re(result_elem_t& re, std::integer_sequence<Int, i...> is) {
    re.set(stmt_col_v<i>()...);
  }

  sqlite3_stmt* stmt_;
  MakeResultElem make_result_elem_;
};

template<class Config>
struct db {
  db(Config&& config) {
    sqlite3_open(config.file_path, &db_);
    if( db_ == nullptr ) {
      throw std::runtime_error("sqlite db open failed");
    }
  }
  template<class MakeResultElem>
  auto select(const std::string& sql, MakeResultElem&& make_result_elem) {
    sqlite3_stmt* stmt;
    auto ec = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr);
    if(ec != SQLITE_OK) {
      throw std::runtime_error("sqlite db select failed");
    }
    dataset_range<MakeResultElem> dr {stmt, std::forward<MakeResultElem>(make_result_elem)};
    return dr;
  }
private:
  sqlite3* db_;
};



}