#pragma once
#include "tuple/trans.hpp"

namespace avalon {

template<class Tuple> struct is_tuple : public std::false_type {};
template<class... T>  struct is_tuple<std::tuple<T...>> : public std::true_type {};
template<class Tuple> constexpr bool is_tuple_v = is_tuple<Tuple>::value;

}