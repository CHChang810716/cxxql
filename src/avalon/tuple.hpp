#pragma once
#include "tuple/trans.hpp"
#include "tuple/unique.hpp"
namespace avalon {

template<class Tuple> struct is_tuple : public std::false_type {};
template<class... T>  struct is_tuple<std::tuple<T...>> : public std::true_type {};
template<class Tuple> constexpr bool is_tuple_v = is_tuple<Tuple>::value;

template<class... T>
decltype(auto) make_tuple(T&&... o) {
  return std::tuple<T...>{std::forward<T>(o)...};
}

}