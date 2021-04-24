#pragma once
#include <string>
#include <cxxql/to_sql/utils.hpp>

namespace cxxql::expr {

template<class Table>
struct create_table_if_not_exists_t {
  Table table;
};

template<class Table>
auto create_table_if_not_exists(const Table& tab) {
  return create_table_if_not_exists_t<const Table&> {tab};
}

}

namespace cxxql::to_sql_ns {

template<class Driver, class Tab>
std::string create_table_if_not_exists(
  Driver& driver, 
  const Tab& table,
  const std::string& table_name
) {
  return fmt::format(
    "CREAT TABLE IF NOT EXISTS {} ;", 
    table_name
  );
}
  
} // namespace cxxql

namespace cxxql {

template<class Driver, class Table>
auto to_sql(Driver& driver, const cxxql::expr::create_table_if_not_exists_t<Table>& expr) {
  return to_sql_ns::create_table_if_not_exists(
    driver, expr.table, 
    to_sql_ns::table_id(expr::get_table_name(expr.table))
  );
}

using expr::create_table_if_not_exists;

} // namespace cxxql
