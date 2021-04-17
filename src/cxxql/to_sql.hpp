#pragma once
#include <string>
#include "expr.hpp"
#include <avalon/tuple.hpp>
#include "to_sql/create_table.hpp"
#include "to_sql/type.hpp"
#include "to_sql/select.hpp"
#include "to_sql/insert_into.hpp"
#include "to_sql/drop_table.hpp"

namespace cxxql {

template<class Driver, class Table>
auto to_sql(Driver& driver, const cxxql::expr::drop_table_t<Table>& expr) {
  return to_sql_ns::drop_table(
    driver, expr.table, 
    expr::get_table_name(expr.table)
  );
}
template<class Driver, class Tab>
auto to_sql(Driver& driver, const cxxql::expr::create_table_t<Tab>& expr) {
  return to_sql_ns::create_table(driver, expr.table, 
    expr::get_table_name(expr.table),
    avalon::tuple::trans(
      expr::get_table_cols(expr.table),
      [&](const auto& col_design) {
        return to_sql_ns::create_table_col(
          driver, expr.table,
          expr::get_col_name(col_design),
          to_sql_ns::col_type(col_design),
          col_design
        );
      }
    )
  );
}
template<class Driver, class Cols, class Tables, class Where>
auto to_sql(Driver& driver, const cxxql::expr::select_t<Cols, Tables, Where>& expr) {
  return to_sql_ns::select(driver, 
    avalon::tuple::trans(expr.cols, expr::get_col_full_name),
    avalon::tuple::trans(expr.tables, expr::get_table_name),
    to_sql_ns::where(expr.cond)
  ); 
}
template<class Driver, class Table, class Cols>
auto to_sql(Driver& driver, const cxxql::expr::insert_into_t<Table, Cols>& expr) {
  auto to_str = [](auto&& val) {
    return to_sql_ns::value(val);
  };
  return to_sql_ns::insert_into(driver,
    avalon::tuple::trans(expr.cols, expr::get_col_name),
    expr::get_table_name(expr.table),
    avalon::tuple::trans(expr.col_values, to_str)
  );
}

}