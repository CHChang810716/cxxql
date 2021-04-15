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