#pragma once
#include "exec.hpp"
namespace cxxql {

template<class Derived>
struct db {
  using This = db<Derived>;
  auto& derived() {
    return static_cast<Derived&>(*this);
  }
  const auto& derived() const {
    return const_cast<This&>(*this).derived();
  }
  template<class Expr>
  auto operator()(const Expr& expr) {
    return exec(derived(), expr);
  }
  template<class Expr>
  auto operator()(const Expr& expr) const {
    return exec(derived(), expr);
  }
};
  
} // namespace cxxql 