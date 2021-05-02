#pragma once
#include <fmt/format.h>
#include <string>

namespace cxxqldb::postgresql {
template<class Config> struct connection;
}

namespace cxxql::to_sql_ns {
template<class Config, class TName>
std::string table_id(
  cxxqldb::postgresql::connection<Config>& db,
  const TName& table_name, 
  const std::string& var_name = ""
) {
  if(var_name.empty()) {
    return fmt::format("\"{}\"", table_name);
  } else {
    return var_name;
  }
}
template<class Config, class Token>
auto col_id(
  cxxqldb::postgresql::connection<Config>& db,
  const Token& token
) {
  return fmt::format("\"{}\"", token);
}
}

#include <cxxql/to_sql/create_table.hpp>
#define CXXQL_TYPE_TO_PG_AI_SQL(T, expr) \
  std::string pg_ai_type(avalon::mp::identity<T> t) { \
    return expr; \
  }
namespace cxxql::to_sql_ns {
CXXQL_TYPE_TO_PG_AI_SQL(cxxql::integer,   "SERIAL")
CXXQL_TYPE_TO_PG_AI_SQL(cxxql::smallint,  "SMALLSERIAL")
CXXQL_TYPE_TO_PG_AI_SQL(cxxql::bigint,    "BIGSERIAL")

template<class Config, class Tab, class ColDesign>
std::string create_table_col(
  cxxqldb::postgresql::connection<Config>& driver, 
  const Tab& table,
  const std::string& col_name,
  const std::string& _col_type,
  const ColDesign& col_design
) {
  std::string col_type = _col_type;
  if constexpr(has_auto_increment_v<ColDesign>) {
    col_type = pg_ai_type(
      avalon::mp::identity<typename ColDesign::type>{}
    );
  }
  return default_create_table_col(driver, table, col_name, col_type, col_design);
}
}
#undef CXXQL_TYPE_TO_PG_AI_SQL