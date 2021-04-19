#pragma once
#include <string>
#include <avalon/mp/identity.hpp>
#include <cxxql/type.hpp>
#include <fmt/format.h>
#include <cxxql/expr/col_design.hpp>
#define CXXQL_TYPE_TO_SQL(T, expr) \
  std::string type(avalon::mp::identity<T> t) { \
    return expr; \
  }

namespace cxxql::to_sql_ns {

template<std::size_t size>
CXXQL_TYPE_TO_SQL(
  cxxql::varchar<size>, 
  fmt::format("VARCHAR({})", size)
)
CXXQL_TYPE_TO_SQL(cxxql::boolean,  "BOOLEAN")
CXXQL_TYPE_TO_SQL(cxxql::blob,     "BLOB")
CXXQL_TYPE_TO_SQL(cxxql::integer,  "INTEGER")
CXXQL_TYPE_TO_SQL(cxxql::smallint, "SMALLINT")
CXXQL_TYPE_TO_SQL(cxxql::bigint,   "BIGINT")
CXXQL_TYPE_TO_SQL(cxxql::real,     "REAL")

template<class Col>
auto col_type(const Col& col) {
  if constexpr(cxxql::is_col_design_type_v<Col>) {
    return type(avalon::mp::identity<typename Col::type>{});
  } else {
    return type(avalon::mp::identity<typename Col::cxxqltype>{});
  }
}

template<class T>
auto value(const T& v) {
  return std::to_string(v);
}

auto value(const std::string& str) {
  if(str.find("'") != str.npos) {
    std::string tmp;
    for(auto& c : str) {
      if(c == '\'') {
        tmp.append("''");
      } else {
        tmp.push_back(c);
      }
    }
    return fmt::format("'{}'", tmp);
  }
  return fmt::format("'{}'", str);
}

auto value(const char* const& str) {
  return value(std::string(str));
}
}