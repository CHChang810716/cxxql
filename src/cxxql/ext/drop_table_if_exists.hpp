#pragma once
#include <string>

namespace cxxql::expr {

template<class Table>
struct drop_table_if_exists_t {
  Table table;
};

template<class Table>
auto drop_table_if_exists(const Table& tab) {
  return drop_table_if_exists_t<const Table&> {tab};
}

}

namespace cxxql::to_sql_ns {

template<class Driver, class Tab>
std::string drop_table_if_exists(
  Driver& driver, 
  const Tab& table,
  const std::string& table_name
) {
  return fmt::format(
    "DROP TABLE IF EXISTS {} ;", 
    table_name
  );
}
  
} // namespace cxxql

namespace cxxql {

template<class Driver, class Table>
auto to_sql(Driver& driver, const cxxql::expr::drop_table_if_exists_t<Table>& expr) {
  return to_sql_ns::drop_table_if_exists(
    driver, expr.table, 
    expr::get_table_name(expr.table)
  );
}
  
} // namespace cxxql

