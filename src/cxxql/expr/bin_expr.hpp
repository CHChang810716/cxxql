#pragma once
#include <type_traits>
#include <tuple>
#include <utility>
#include <cxxql/expr/utils.hpp>

namespace cxxql::expr {

struct bin_oper {
  enum type{
    EQ, NE, GT, GE, 
    LT, LE, OR, AND,
    ASN
  };
};

template<class Opnds>
struct bin_expr {
  bin_oper::type oper;
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
decltype(auto) make_bin_opnd(T&& o) {
  return std::forward<T>(o);
}
}
#define CXXQL_EXPR_BOP(op, sym) \
  template<class CD0, class CD1,  \
    class C0Check = std::enable_if_t< \
      (cxxql::is_col_design_type_v<CD0> || \
        cxxql::expr::is_bin_expr_v<CD0>) || \
      (cxxql::is_col_design_type_v<CD1> || \
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
#define CXXQL_EXPR_BOP_MEM(op, sym) \
  template<class CD0,  \
    class C0Check = std::enable_if_t< \
      (cxxql::is_col_design_type_v<CD0> || \
        cxxql::expr::is_bin_expr_v<CD0>) \
    > \
  > \
  auto operator op(const CD0& cd0) { \
    auto cols = std::make_tuple( \
      cxxql::expr::make_bin_opnd(*this), \
      cxxql::expr::make_bin_opnd(cd0) \
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
CXXQL_EXPR_BOP(<<, cxxql::expr::bin_oper::ASN)