#pragma once
#include <type_traits>
#include <utility>

#define AVALON_HAS_MEM_VALUE(mem, mem_t) \
  template<class Target> \
  struct has_##mem { \
    template<class... T> \
    static std::false_type check (T&&...) {} \
    template<class T> \
    static auto check(T o) -> typename std::is_same< \
      decltype(o.mem), \
      mem_t \
    >::type {} \
    static constexpr bool value = decltype(check(std::declval<Target>()))::value; \
  }; \
  template<class T> \
  constexpr bool has_##mem##_v = has_##mem<T>::value;
