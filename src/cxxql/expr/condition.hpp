#pragma once
#include <type_traits>
#include <tuple>
#include <utility>
#include <cxxql/expr/utils.hpp>

namespace cxxql::expr {
struct cond_oper {
  enum type{
    EQ, NE, GT, GE, 
    LT, LE, OR, AND
  };
};
template<class Opnds>
struct bin_expr {
  cond_oper::type oper;
  Opnds opnds;
  auto left() const {
    return std::get<0>(opnds);
  }
  auto right() const {
    return std::get<1>(opnds);
  }
};

template<class T>
struct is_bin_expr {
  constexpr static bool value = false;
};

template<class T>
struct is_bin_expr<bin_expr<T>> {
  constexpr static bool value = true;
};

template<class T>
constexpr bool is_bin_expr_v = is_bin_expr<T>::value;

template<class T>
auto make_bin_opnd(const T& o) {
  if constexpr(std::is_convertible_v<T, col_design>) {
    return col_design_to_col(o);
  } else {
    return o;
  }
}

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

CXXQL_EXPR_BOP(==, cxxql::expr::cond_oper::EQ )
CXXQL_EXPR_BOP(!=, cxxql::expr::cond_oper::NE )
CXXQL_EXPR_BOP(> , cxxql::expr::cond_oper::GT )
CXXQL_EXPR_BOP(>=, cxxql::expr::cond_oper::GE )
CXXQL_EXPR_BOP(< , cxxql::expr::cond_oper::LT )
CXXQL_EXPR_BOP(<=, cxxql::expr::cond_oper::LE )
CXXQL_EXPR_BOP(||, cxxql::expr::cond_oper::OR )
CXXQL_EXPR_BOP(&&, cxxql::expr::cond_oper::AND)