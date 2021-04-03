#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include "utils.hpp"
#include "condition.hpp"
#include <avalon/tuple/trans.hpp>
namespace cxxql::expr {

template<class Table, class Cols>
struct insert_into_t {
  using values_t = avalon::tuple::type_trans_t<Cols, col_value_cxx_t>;

  Table     table;
  Cols      cols;
  values_t  col_values;
};

template<class Table, class Cols>
struct insert_into_pre0_t {
  template<class... T>
  auto values(T&&... vs) && {
    insert_into_t<Table, Cols> insert_into_expr {table, std::move(cols)};
    assign_values(
      insert_into_expr,
      std::forward_as_tuple(std::forward<T>(vs)...),
      std::make_index_sequence<sizeof...(T)>()
    );
    return insert_into_expr;
  }
  Table table ;
  Cols  cols  ;
private:
  template<class T, T i, class ValTuple>
  int assign_value(
    insert_into_t<Table, Cols>& insert_into_expr,
    ValTuple&& vt
  ) {
    std::get<i>(insert_into_expr.col_values) = std::get<i>(vt);
    return 0;
  }
  template<class ValTuple, class T, T... i>
  void assign_values(
    insert_into_t<Table, Cols>& insert_into_expr,
    ValTuple&& vt, 
    std::integer_sequence<T, i...> seq
  ) {
    auto list = {assign_value<T, i>(insert_into_expr, vt)...};
  }
};


template<class... RawCols>
auto insert_into(const RawCols&... raw_cols) {
  auto cols = std::make_tuple(raw_cols...);
  auto& table = col_to_table(std::get<0>(cols));
  return insert_into_pre0_t<decltype(table), decltype(cols)>{
    table,
    std::move(cols)
  };
}
    
} // namespace cxxql::expr
