#pragma once
#include <utility>
namespace avalon::integer_sequence {

template<class Int, Int i, class IS>
struct push_front {};

template<class Int, Int k, Int... i>
struct push_front<Int, k, std::integer_sequence<Int, i...>>
{
  using type = std::integer_sequence<Int, k, i...>;
};

template<class Int, Int i, class IS>
using push_front_t = typename push_front<Int, i, IS>::type;


}