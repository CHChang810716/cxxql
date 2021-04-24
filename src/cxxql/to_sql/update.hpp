#pragma once
#include <string>
#include "bin_expr.hpp"
#include <iostream>
#include "utils.hpp"

namespace cxxql::to_sql_ns {
template<class Driver, class Expr>
auto update_set_col_expr(Driver& driver, const Expr& expr) {
  auto res = bin_expr(expr, [&driver](const auto& str){
    return col_id(driver, cxxql::expr::get_col_name(str));
  }, "{} {} {}");
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
