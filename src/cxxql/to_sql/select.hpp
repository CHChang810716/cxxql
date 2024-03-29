#pragma once
#include <string>
#include <vector>
#include <fmt/format.h>
#include "utils.hpp"
#include "type.hpp"
#include <cxxql/expr/select.hpp>
#include "bin_expr.hpp"

namespace cxxql::to_sql_ns {

template<class Driver, class Where>
std::string where(Driver& driver, const Where& w) {
  if constexpr(std::is_same_v<Where, expr::empty_where>) {
    return "";
  } else {
    return fmt::format(" WHERE {}", bin_expr(
      w.expr, 
      [&](const auto& col) {
        return col_full_id(driver, expr::get_col_full_name(col));
      }
    ));
  }
}

template<class Driver, class SelColStrs, class FromTableStrs>
auto select(
  Driver& driver, 
  const SelColStrs&     sel_cols,
  const FromTableStrs&  from_tables,
  const std::string&    where_cond
) {
  return fmt::format(
    "SELECT {} FROM {}{} ;",
    tuple_to_string(",", sel_cols),
    tuple_to_string(",", from_tables),
    where_cond
  );
}
  
} // namespace cxxql::to_sql
