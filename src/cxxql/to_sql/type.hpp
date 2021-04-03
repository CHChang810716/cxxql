#pragma once
#include <string>
#include <avalon/mp/identity.hpp>
#include <cxxql/type.hpp>
#include <fmt/format.h>
#define CXXQL_TYPE_TO_SQL(T, expr) \
  std::string type(avalon::mp::identity<T> t) { \
    return expr; \
  }

namespace cxxql::to_sql {

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
  if constexpr(std::is_convertible_v<Col, expr::col_design>) {
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
  return fmt::format("'{}'", str);
}

}