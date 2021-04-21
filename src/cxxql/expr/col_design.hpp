#pragma once
#include <type_traits>
#include <avalon/macro/has_mem.hpp>
// namespace cxxql::expr {
// struct col_design {};
// 
// }
// namespace cxxql {
// 
// template<class T>
// constexpr bool is_col_design_type_v = std::is_convertible_v<T, expr::col_design>;
// 
// }
namespace cxxql {

AVALON_HAS_MEM_VALUE(__cxxql_col_test, bool);
template<class T>
constexpr bool is_col_design_v(const T& o) {
  return has___cxxql_col_test<T>::value;
}
template<class T>
constexpr bool is_col_design_type_v = has___cxxql_col_test<T>::value;

}