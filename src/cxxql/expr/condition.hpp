#pragma once
#include <type_traits>
#include <tuple>
#include <utility>
#include <cxxql/expr/utils.hpp>
#include "bin_expr.hpp"

namespace cxxql::expr {

struct empty_where {};
template<class... T>
struct where_t {
  bin_expr<T...> expr;
};

}
#define CXXQL_EXPR_BOP(op, sym) \
  template<class CD0, class CD1,  \
    class C0Check = std::enable_if_t< \
      (std::is_convertible_v<CD0, cxxql::expr::col_design> || \
      cxxql::expr::is_bin_expr_v<CD0>) || \
      (std::is_convertible_v<CD1, cxxql::expr::col_design> || \
      cxxql::expr::is_bin_expr_v<CD1>) \
    > \
  > \
  auto operator op(const CD0& cd0, const CD1& cd1) { \
    auto cols = std::make_tuple( \
      cxxql::expr::make_bin_opnd(cd0), \
      cxxql::expr::make_bin_opnd(cd1) \
    ); \
    return cxxql::expr::bin_expr<decltype(cols)>{sym, std::move(cols)}; \
  }

CXXQL_EXPR_BOP(==, cxxql::expr::bin_oper::EQ )
CXXQL_EXPR_BOP(!=, cxxql::expr::bin_oper::NE )
CXXQL_EXPR_BOP(> , cxxql::expr::bin_oper::GT )
CXXQL_EXPR_BOP(>=, cxxql::expr::bin_oper::GE )
CXXQL_EXPR_BOP(< , cxxql::expr::bin_oper::LT )
CXXQL_EXPR_BOP(<=, cxxql::expr::bin_oper::LE )
CXXQL_EXPR_BOP(||, cxxql::expr::bin_oper::OR )
CXXQL_EXPR_BOP(&&, cxxql::expr::bin_oper::AND)