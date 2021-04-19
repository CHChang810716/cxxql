#pragma once
#include "expr.hpp"
#include "exec/dataset_range.hpp"
namespace cxxql {

template<class Driver, class Expr>
std::string to_sql(Driver& db, const Expr& expr);

template<class Driver, class Expr>
auto exec(Driver& db, const Expr& expr) {
  auto sql_str = to_sql(db, expr);
  return db.exec(sql_str);
}

template<class Driver, class... SelectArgs>
auto exec(Driver& db, const expr::select_t<SelectArgs...>& expr) {
  using expr_t = expr::select_t<SelectArgs...>;
  using res_elem_t = typename expr_t::result_elem_t;
  auto sql_str = to_sql(db, expr);
  auto&& iterator_core = db.template select<res_elem_t>(sql_str);
  return exec_ns::make_dataset_range(
    std::forward<decltype(iterator_core)>(iterator_core)
  );
}

}