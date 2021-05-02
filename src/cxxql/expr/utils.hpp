#pragma once
#include <string>
#include <avalon/macro/foreach.hpp>
#include <cxxql/type.hpp>
#include "col_design.hpp"
#include <fmt/format.h>
#include "table_var.hpp"


namespace cxxql::expr {

struct table_token {
  std::string table_name;
  std::string var_name;
};

constexpr auto get_table_name = [](const auto& tab) {
  using Tab = std::remove_cv_t<decltype(tab)>;
  return __cxxql_table_name(tab);
};
constexpr struct {
  template<class Tab>
  auto operator()(const Tab& tab) const {
    return table_token{__cxxql_table_name(tab), ""};
  }
  template<class Tab>
  auto operator()(const table_var_t<Tab>& tab) const {
    return table_token{__cxxql_table_name(tab), tab.symbol};
  }
} get_table_full_name;
// constexpr auto get_table_full_name = [](const auto& tab) {
//   using Tab = std::remove_cv_t<decltype(tab)>;
//   if constexpr (is_table_var_v<Tab>) {
//   } else {
//   }
// };

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

struct col_token {
  table_token table;
  std::string col;
  auto general_dot_format() const {
    return fmt::format("{}.{}", table.table_name, col);
  }
};

constexpr auto get_col_full_name = [](const auto& col) {
  using Col = std::remove_cv_t<decltype(col)>;
  auto lambda = [](const auto& cd, const auto& col) {
    table_token tt{
      get_table_name(col.__cxxql_table()),
      cd.table_var_name()
    };
    return col_token {tt, col.__cxxql_name};
  };
  if constexpr(cxxql::is_col_design_type_v<Col>) {
    auto c = __cxxql_col(col);
    return lambda(col, c);
  } else {
    const auto& cd = col.__cxxql_col_design();
    return lambda(cd, col);
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