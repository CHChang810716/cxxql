#pragma once
#include <tuple>
#include <utility>
#include <avalon/integer_sequence/push_front.hpp>

namespace avalon::tuple {

template<class T, class... TS>
struct is_contain {};

template<class T, class TS0, class... TS>
struct is_contain<T, TS0, TS...>  : public std::conditional_t<
  std::is_same_v<T, TS0>,
  std::true_type,
  is_contain<T, TS...>
>{};

template<class T>
struct is_contain<T> : public std::false_type {};

template<class... T>
constexpr bool is_contain_v = is_contain<T...>::value;

template<class T, class Tuple>
struct type_push_front {};

template<class T, class... TT>
struct type_push_front<T, std::tuple<TT...>> {
  using type = std::tuple<T, TT...>;
};

template<class T, class Tuple>
using type_push_front_t = typename type_push_front<T, Tuple>::type;

template<class Tuple, class IS>
struct type_unique_impl {};

template<class T0, class... T, class Int, Int i0, Int... i>
struct type_unique_impl<std::tuple<T0, T...>, std::integer_sequence<Int, i0, i...>> {
  static constexpr bool __is_contain = is_contain_v<T0, T...>;
  using __next = type_unique_impl<std::tuple<T...>, std::integer_sequence<Int, i...>>;
  using type = std::conditional_t<
    __is_contain,
    typename __next::type,
    type_push_front_t<T0, typename __next::type>
  >;
  using index = std::conditional_t<
    __is_contain,
    typename __next::index,
    avalon::integer_sequence::push_front_t<Int, i0, typename __next::index>
  >;
};

template<class IS>
struct type_unique_impl<std::tuple<>, IS> {
  using type = std::tuple<>;
  using index = IS;
};

template<class Tuple>
using type_unique = type_unique_impl<
  Tuple, 
  std::make_index_sequence<std::tuple_size_v<Tuple>>
>;

// template<class RTuple, class Tuple, class Int, Int... i>
// auto unique_impl(Tuple&& tup, std::integer_sequence<Int, i...> is) {
//   return RTuple{std::get<i>(tup)...};
// }
// template<class Tuple>
// auto unique(Tuple&& tuple) {
//   using unique_pack = type_unique<std::remove_reference_t<Tuple>>;
// }
  
} // namespace avalon::tuple 