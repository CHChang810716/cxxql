#pragma once
#include <tuple>
#include <string>
#include <fmt/format.h>
#include "utils.hpp"
#include "type.hpp"
#include <avalon/macro/has_mem.hpp>
namespace cxxql::to_sql_ns {

template<class Driver, class Tab, class... ColElemStrs>
std::string create_table(
  Driver& driver, 
  const Tab& table,
  const std::string& table_name,
  const std::tuple<ColElemStrs...>& col_elems
) {
  return fmt::format(
    "CREATE TABLE {} ({}) ;",
    table_name,
    tuple_to_string(
      ",",
      col_elems
    )
  );
}

AVALON_HAS_MEM_VALUE(default_value, cxxtype_t<typename T::type>)
AVALON_HAS_MEM_VALUE(unique, bool)
AVALON_HAS_MEM_VALUE(primary_key, bool)
AVALON_HAS_MEM_VALUE(not_null, bool)
AVALON_HAS_MEM_VALUE(auto_increment, bool)


template<class Driver, class Tab, class ColDesign>
std::string default_create_table_col(
  Driver& driver, 
  const Tab& table,
  const std::string& col_name,
  const std::string& col_type,
  const ColDesign& col_design
) {
  auto basic = fmt::format("{} {}", col_name, col_type);
  if constexpr (has_not_null_v<ColDesign>) {
    if(col_design.not_null) {
      basic += " NOT NULL";
    }
  }
  if constexpr (has_default_value_v<ColDesign>) {
    basic += fmt::format(" DEFAULT {}", value(col_design.default_value));
  }
  if constexpr (has_primary_key_v<ColDesign>) {
    if(col_design.primary_key) {
      basic += " PRIMARY KEY";
    }
  }
  if constexpr (has_unique_v<ColDesign>) {
    if(col_design.unique) {
      basic += " UNIQUE";
    }
  }
  return basic;
}
template<class Driver, class Tab, class ColDesign>
std::string create_table_col(
  Driver& driver, 
  const Tab& table,
  const std::string& col_name,
  const std::string& col_type,
  const ColDesign& col_design
) {
  return default_create_table_col(driver, table, col_name, col_type, col_design);
}

}