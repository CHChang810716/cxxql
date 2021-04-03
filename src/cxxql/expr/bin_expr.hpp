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
auto make_bin_opnd(const T& o) {
  if constexpr(std::is_convertible_v<T, col_design>) {
    return col_design_to_col(o);
  } else {
    return o;
  }
}
}