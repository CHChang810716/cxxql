#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include "utils.hpp"
#include "condition.hpp"
namespace cxxql::expr {
template<class Cols, class Tables, class Where = empty_where>
struct select_base_t {
  Cols    cols;
  Tables  tables;
  Where   cond;
};

template<class Cols, class Tables, class Where = empty_where>
struct select_t : public select_base_t<Cols, Tables, Where> {
};

template<class Cols, class Tables>
struct select_t<Cols, Tables, empty_where> : public select_base_t<Cols, Tables, empty_where> {
  template<class... T>
  auto where(bin_expr<T...>&& wexpr) const && {
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

template<class... RawCols>
auto select(const RawCols&... raw_cols) {
  auto cols = std::make_tuple(raw_cols...);
  auto tables = std::make_tuple(col_to_table(raw_cols)...);
  return select_t<decltype(cols), decltype(tables)>{
    std::move(cols), 
    std::move(tables),
    empty_where{}
  };
}
    
} // namespace cxxql::expr
