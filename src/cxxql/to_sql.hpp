#pragma once
#include <string>
#include "expr.hpp"
#include <avalon/tuple.hpp>
#include "to_sql/create_table.hpp"
#include "to_sql/type.hpp"
namespace cxxql {

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
  
}

}