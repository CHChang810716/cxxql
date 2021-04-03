#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include "utils.hpp"
#include "condition.hpp"
#include <avalon/tuple.hpp>
namespace cxxql::expr {

template<class Table>
struct update_pre0_t {
  Table table;
};
template<
  class Table, 
  class ColASNs, 
  class = std::enable_if_t<avalon::is_tuple_v<ColASNs>>
>
struct update_pre1_t {
  ColASNs col_asns;
};
template<class Table, class ColASNs, class Where = empty_where>
struct update_t {

  template<class... Exprs>
  auto set(Exprs&&... exprs) {
    return *this;
  }

  template<class... T>
  auto where(bin_expr<T...>&& wexpr) const {
    return update_t<
      Table,
      ColASNs,
      where_t<T...>
    > {
      table,
      col_asns,
      where_t<T...>{std::move(wexpr)}
    };
  }
  Table     table;
  ColASNs   col_asns;
  Where     cond;
};

template<class... RawCols>
auto update(const RawCols&... raw_cols) {
  auto cols = std::make_tuple(raw_cols...);
  auto tables = std::make_tuple(col_to_table(raw_cols)...);
  return update_t<decltype(cols), decltype(tables)>{
    std::move(cols), 
    std::move(tables),
    empty_where{}
  };
}
    
} // namespace cxxql::expr
