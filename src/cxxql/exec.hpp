#pragma once
#include "expr.hpp"
#include "to_sql.hpp"
#include "exec/dataset_range.hpp"
namespace cxxql {

template<class Driver, class Expr>
auto exec(Driver& db, const Expr& expr) {}

template<class Driver, class... SelectArgs>
auto exec(Driver& db, const expr::select_t<SelectArgs...>& expr) {
  using expr_t = expr::select_t<SelectArgs...>;
  using res_elem_t = typename expr_t::result_elem_t;
  auto sql_str = to_sql(db, expr);
  auto&& iterator_core = db.select(sql_str, [expr]() {
    return expr.make_result_elem();
  });
  return exec_ns::make_dataset_range(
    std::forward<decltype(iterator_core)>(iterator_core)
  );
}



}