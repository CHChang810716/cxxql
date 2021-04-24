#pragma once
#include <tuple>
#include <string>
#include <fmt/format.h>
namespace cxxql::to_sql_ns {

namespace detail { 
template<class Delim, class Tuple, class Int, Int... i> 
auto tuple_to_string_impl(
  const Delim& delim, 
  const Tuple& tup,
  std::integer_sequence<Int, i...> is
) { 
  return (std::get<0>(tup) + ... + (delim + std::get<i + 1>(tup)));
}
}
std::string args_to_string(const std::string& delim) {
  return "";
}
template<class Str0, class... Strs>
std::string args_to_string(
  const std::string& delim,
  const Str0& arg0,
  const Strs&... args
) {
  if constexpr(sizeof...(Strs) == 0) {
    return arg0;
  } else {
    return (arg0 + ... + (delim + args));
  }
}


template<class... Strs>
std::string tuple_to_string(
  const std::string& delim,
  const std::tuple<Strs...>& tup
) {
  if constexpr(sizeof...(Strs) == 0) {
    return "";
  } else {
    return detail::tuple_to_string_impl(
      delim, tup, std::make_integer_sequence<
        std::size_t, sizeof...(Strs) - 1
      >()
    );
  }
}

template<class Driver, class Str>
auto table_id(Driver& driver, const Str& name) {
  return name;
}
template<class Driver, class Str>
auto col_id(Driver& driver, const Str& token) {
  return token;
}
template<class Driver, class ColToken>
auto col_full_id(Driver& driver, const ColToken& token) {
  return fmt::format("{}.{}", 
    table_id(driver, token.table),
    col_id(driver, token.col)
  );
}
  
} // namespace cxxql::to_sql
