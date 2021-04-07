#pragma once
#include "expr.hpp"
#include "to_sql.hpp"
namespace cxxql {

template<class Driver, class Expr>
auto exec(Driver& db, const Expr& expr) {}

template<class Driver, class... SelectArgs>
auto exec(Driver& db, const expr::select_t<SelectArgs...>& expr) {
  auto sql_str = to_sqlstr(db, expr);
  

}



}