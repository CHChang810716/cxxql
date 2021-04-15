#pragma once
#include <type_traits>
namespace cxxql::expr {
struct col_design {};

}
// namespace cxxql {
// 
// template<class T>
// constexpr bool is_col_design_type_v = std::is_convertible_v<T, expr::col_design>;
// 
// }
namespace cxxql {

template<class Target>
struct has___cxxql_col_test {
  template<class... T>
  static std::false_type check (T&&...) {}
  template<class T>
  static auto check(T o) -> typename std::is_same<
    decltype(o.__cxxql_col_test), bool
  >::type {}
  static constexpr bool value = decltype(check(std::declval<Target>()))::value;
};
template<class T>
constexpr bool is_col_design_v(const T& o) {
  return has___cxxql_col_test<T>::value;
}
template<class T>
constexpr bool is_col_design_type_v = has___cxxql_col_test<T>::value;

}