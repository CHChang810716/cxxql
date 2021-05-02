#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include "utils.hpp"
#include "condition.hpp"
#include <avalon/lexical_cast.hpp>
#include <avalon/mp/identity.hpp>
#include <avalon/tuple/unique.hpp>
#include "table_var.hpp"
namespace cxxql::expr {

template<class ColDesign, class = std::enable_if_t<
  cxxql::is_col_design_type_v<ColDesign>
>>
struct col_design_to_col_type {
  using type = decltype(col_design_to_col(ColDesign{}));
};

template<class ColDesign>
using col_design_to_col_t = typename col_design_to_col_type<ColDesign>::type;

template<class ColDesignTuple>
struct select_result_elem_t
{};

template<class... ColDesigns>
struct select_result_elem_t<std::tuple<ColDesigns...>>
: public col_design_to_col_t<ColDesigns>...
{
  static constexpr std::size_t col_num = sizeof...(ColDesigns);

  using col_d_tuple = std::tuple<ColDesigns...>;

  template<std::size_t i>
  using col_d = std::tuple_element_t<i, col_d_tuple>;

  template<std::size_t i>
  using col_t = col_design_to_col_t<col_d<i>>;

  template<std::size_t i>
  using col_cxxtype = col_value_cxx_t<col_d<i>>;

  template<std::size_t i>
  using col_cxxqltype = typename col_d<i>::type;

  template<std::size_t i>
  col_cxxtype<i>& get() {
    return static_cast<col_t<i>&>(*this).get_col();
  }
  template<class CD>
  auto& get_col(const CD& col_design) {
    return static_cast<col_design_to_col_t<CD>&>(*this).get_col();
  }

  auto& set_from_strs(
    avalon::mp::type_replace_t<ColDesigns, const std::string&>... strs
  ) {
    return set(
      avalon::lexical_cast<col_value_cxx_t<ColDesigns>>(strs)...
    );
  }
  auto& set(col_value_cxx_t<ColDesigns>&&... v) {
    auto a = {set_col<ColDesigns>(std::move(v))...};
    return *this;
  }
  template<class ColDesign>
  auto& set_col(col_value_cxx_t<ColDesign>&& v) {
    static_cast<col_design_to_col_t<ColDesign>&>(*this).set_col(std::move(v));
    return *this;
  }
private:
};

template<class Cols, class Tables, class Where = empty_where>
struct select_base_t {
  using result_elem_t = select_result_elem_t<Cols>;

  auto make_result_elem() const {
    return make_result_elem_impl(
      std::make_integer_sequence<std::size_t, std::tuple_size_v<Cols>>()
    );
  }  

  Cols    cols;
  Tables  tables;
  Where   cond;
private:
  template<class Int, Int... i>
  inline auto make_result_elem_impl(
    std::integer_sequence<Int, i...> is
  ) const {
    return result_elem_t {col_design_to_col(std::get<i>(cols))...};
  }
};

template<class Cols, class Tables, class Where = empty_where>
struct select_t : public select_base_t<Cols, Tables, Where> {

  template<class... T>
  std::enable_if_t<
    std::is_same_v<Where, empty_where>,
    select_t<
      Cols,
      std::tuple<T...>,
      Where
    >
  > from(T... tables) {
    return select_t<Cols, std::tuple<T...>, Where> {
      std::move(this->cols),
      std::make_tuple(std::move(tables)...),
      Where {}
    };
  }

  template<class... T>
  std::enable_if_t<
    std::is_same_v<Where, empty_where>,
    select_t<
      Cols,
      Tables,
      where_t<T...>
    >
  > where(bin_expr<T...>&& wexpr) const &&{
    return select_t<
      Cols,
      Tables,
      where_t<T...>
    > {
      std::move(this->cols),
      std::move(this->tables),
      where_t<T...>{std::move(wexpr)}
    };
  }
};

template<class T, class... TS> struct is_contain_except_table_var {};

template<class Table, class... TS> 
struct is_contain_except_table_var<
  table_var_t<Table>, TS...
> : public std::false_type {};

template<class T, class TS0, class... TS>
struct is_contain_except_table_var<T, TS0, TS...>  : public std::conditional_t<
  std::is_same_v<T, TS0>,
  std::true_type,
  is_contain_except_table_var<T, TS...>
>{};

template<class T>
struct is_contain_except_table_var<T> : public std::false_type {};

template<class... T>
constexpr bool is_contain_except_table_var_v = is_contain_except_table_var<T...>::value;

template<class... RawCols>
auto select(const RawCols&... raw_cols) {
  auto cols = std::make_tuple(raw_cols...);
  auto col_tables = std::make_tuple(col_to_table(raw_cols)...);
  using tu = avalon::tuple::type_unique<
    decltype(col_tables), 
    is_contain_except_table_var
  >;
  typename tu::type tables;
  return select_t<decltype(cols), typename tu::type, empty_where>{
    std::move(cols), 
    std::move(tables),
    empty_where{}
  };
}
    
} // namespace cxxql::expr
