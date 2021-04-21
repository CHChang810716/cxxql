#pragma once
#include <string>
#include <cxxql/to_sql/create_table.hpp>
namespace cxxqldb::sqlite {
template<class Config> class db;
}
namespace cxxql::to_sql_ns {
template<class Config, class Tab, class ColDesign>
std::string create_table_col(
  cxxqldb::sqlite::db<Config>& driver, 
  const Tab& table,
  const std::string& col_name,
  const std::string& col_type,
  const ColDesign& col_design
) {
  auto basic = default_create_table_col(driver, table, col_name, col_type, col_design);
  if constexpr(has_auto_increment_v<ColDesign>) {
    if(col_design.auto_increment) {
      basic += " AUTOINCREMENT";
    }
  }
  return basic;
}

}