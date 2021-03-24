#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include "table.hpp"
#include "utils.hpp"
#include "condition.hpp"
#include <avalon/tuple/trans.hpp>
namespace cxxql::expr {

template<class Table, class Cols>
struct insert_into_t {
  using values_t = avalon::tuple::type_trans_t<Cols, col_value_cxx_t>;

  template<class... T>
  auto& values(T&&... vs) {
    assign_values(
      std::forward_as_tuple(std::forward<T>(vs)),
      std::make_index_sequence<sizeof...(T)>
    );
    return *this;
  }
  Table table;
  Cols cols;
  values_t values;
private:
  template<class ValTuple, class T, T... i>
  void assign_values(
    ValTuple&& vt, 
    std::integer_sequence<T, i...> seq = std::make_index_sequence<
      std::tuple_size<ValTuple>
    >{}
  ) {
    (std::get<i>(values) = std::get<i>(vt))...;
  }
};


template<class Table, class... RawCols>
auto insert_into(class Table& table, const RawCols&... raw_cols) {
  auto cols = std::make_tuple(raw_cols...);
  return insert_into_t<decltype(table), decltype(cols)>{
    table,
    std::move(cols),
    {}
  };
}
    
} // namespace cxxql::expr
