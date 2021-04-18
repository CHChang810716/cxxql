#pragma once
#include <string>
#include <fmt/format.h>
namespace cxxql::to_sql_ns {

template<class Driver, class Tab>
std::string drop_table(
  Driver& driver, 
  const Tab& table,
  const std::string& table_name
) {
  return fmt::format("DROP TABLE {} ;", table_name);
}

} // namespace to_sql_ns
