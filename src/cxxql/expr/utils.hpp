#pragma once
#include <string>
#include <avalon/macro/foreach.hpp>
#include <cxxql/type.hpp>
#include <cxxql/table.hpp>

namespace cxxql::expr {

template<class Tab>
auto get_table_name(const Tab& tab) {
  return __cxxql_table_name(tab);
}

template<class ColDng>
auto get_col_design_name(const ColDng& col_dng) {
  return __cxxql_col(col_dng).__cxxql_name;
}

template<class Col>
auto get_col_name(const Col& col) {
  if constexpr(std::is_convertible_v<Col, col_design>) {
    return __cxxql_col(col).__cxxql_name;
  } else {
    return col.__cxxql_name;
  }
}

template<class Col>
auto get_col_full_name(const Col& col) {
  if constexpr(std::is_convertible_v<Col, col_design>) {
    auto c = __cxxql_col(col);
    return get_table_name(c.__cxxql_table) + ("." + c.__cxxql_name);
  } else {
    return get_table_name(col.__cxxql_table) + ("." + col.__cxxql_name);
  }
}

template<class ColDng>
auto col_design_to_col(const ColDng& col_dng) {
  return __cxxql_col(col_dng);
}

template<class Col>
auto& get_table_from_col(const Col& col) {
  if constexpr(std::is_convertible_v<Col, col_design>) {
    return __cxxql_col(col).__cxxql_table;
  } else {
    return col.__cxxql_table;
  }
}

struct dummy_table {};

template<class T>
auto& col_to_table(const T& o) {
  if constexpr(std::is_same_v<T, std::string>) { // column specify in string, not ORM
    return dummy_table {};
  } else {
    return get_table_from_col(o);
  }
}

template<class Table>
auto get_table_cols(const Table& t) {
  return __cxxql_table_cols(t);
}

template<class Col> 
using type_col_to_table_t = std::remove_cv_t<
  decltype(get_table_from_col(Col{}))
>;

template<
  class Col, 
  bool is_col_design = std::is_convertible_v<Col, col_design>
>
struct col_value_cxx {
  using type = typename Col::cxxtype;
};
template<class Col>
struct col_value_cxx<Col, true> {
  using type = typename std::remove_cv_t<
    decltype(__cxxql_col(Col{}))
  >::cxxtype;
};

template<class Col>
using col_value_cxx_t = typename col_value_cxx<
  Col, 
  std::is_convertible_v<Col, col_design>
>::type;

// template<class Col, class = std::enable_if_t<
//   std::is_convertible_v<Col, col_design>
// >>
// using col_value_cxx_t = typename std::remove_cv_t<decltype(__cxxql_col(Col{}))>::cxxtype;
// 
// template<class Col, class = std::enable_if_t<
//   !std::is_convertible_v<Col, col_design>
// >>
// using col_value_cxx_t = typename Col::cxxtype;


}