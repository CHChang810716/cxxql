#pragma once
#include <tuple>
#include <string>
#include <fmt/format.h>
#include "utils.hpp"
#include "type.hpp"
namespace cxxql::to_sql {

template<class Driver, class Tab, class... ColElemStrs>
std::string create_table(
  Driver& driver, 
  const Tab& table,
  const std::string& table_name,
  const std::tuple<ColElemStrs...>& col_elems
) {
  return fmt::format(
    "CREATE TABLE {} ({}) ;",
    table_name,
    tuple_to_string(
      ",",
      col_elems
    )
  );
}

template<class ColDesign>
struct has_default_value {
  template<class... T>
  static std::false_type check (T&&...) {}
  template<class T>
  static auto check(T o) -> typename std::is_convertible<
    decltype(o.default_value),
    cxxtype_t<typename T::type>
  >::type {}
  static constexpr bool value = decltype(check(ColDesign()))::value;
};

template<class T>
constexpr bool has_default_value_v = has_default_value<T>::value;


template<class Driver, class Tab, class ColDesign>
std::string create_table_col(
  Driver& driver, 
  const Tab& table,
  const std::string& col_name,
  const std::string& col_type,
  const ColDesign& col_design
) {
  auto basic = fmt::format("{} {}", col_name, col_type);
  if constexpr (has_default_value_v<ColDesign>) {
    basic += fmt::format(" DEFAULT {}", value(col_design.default_value));
  }
  return basic;
}

}