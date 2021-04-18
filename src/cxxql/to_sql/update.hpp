#pragma once
#include <string>
#include "bin_expr.hpp"
#include <iostream>

namespace cxxql::to_sql_ns {
template<class Expr>
auto update_set_col_expr(const Expr& expr) {
  auto res = bin_expr(expr, cxxql::expr::get_col_name, "{} {} {}");
  return res;
}
template<class Driver, class SetCols>
auto update(
  Driver& driver, 
  const std::string& table_name,
  const SetCols&     sel_cols,
  const std::string& where_cond
) {
  return fmt::format(
    "UPDATE {} SET {}{} ;",
    table_name,
    tuple_to_string(",", sel_cols),
    where_cond
  );
}
  
} // namespace cxxql::to_sql_ns
