#pragma once
#include <string>
#include <avalon/macro/foreach.hpp>
#include <cxxql/type.hpp>
#include "col_design.hpp"

namespace cxxql::expr {

constexpr auto get_table_name = [](const auto& tab) {
  using Tab = std::remove_cv_t<decltype(tab)>;
  return __cxxql_table_name(tab);
};

template<class ColDng>
auto get_col_design_name(const ColDng& col_dng) {
  return __cxxql_col(col_dng).__cxxql_name;
}

constexpr auto get_col_name = [](const auto& col) {
  using Col = std::remove_cv_t<decltype(col)>;
  std::string res;
  if constexpr(cxxql::is_col_design_type_v<Col>) {
    res = __cxxql_col(col).__cxxql_name;
  } else {
    res = col.__cxxql_name;
  }
  return res;
};

constexpr auto get_col_full_name = [](const auto& col) {
  using Col = std::remove_cv_t<decltype(col)>;
  if constexpr(cxxql::is_col_design_type_v<Col>) {
    auto c = __cxxql_col(col);
    return get_table_name(c.__cxxql_table()) + ("." + c.__cxxql_name);
  } else {
    return get_table_name(col.__cxxql_table()) + ("." + col.__cxxql_name);
  }
};

constexpr auto col_design_to_col = [](const auto& col_dng) {
  using Col = std::remove_cv_t<decltype(col_dng)>;
  if constexpr(cxxql::is_col_design_type_v<Col>) {
    return __cxxql_col(col_dng);
  }
};

template<class Col>
auto& get_table_from_col(const Col& col) {
  if constexpr(is_col_design_type_v<Col>) {
    return __cxxql_col(col).__cxxql_table();
  } else {
    return col.__cxxql_table();
  }
}

struct dummy_table_t {} dummy_table;

template<class T>
auto& col_to_table(const T& o) {
  if constexpr(std::is_same_v<T, std::string>) { // column specify in string, not ORM
    return dummy_table;
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
  bool is_col_design = cxxql::is_col_design_type_v<Col>
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
  cxxql::is_col_design_type_v<Col>
>::type;


}