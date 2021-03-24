#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include "table.hpp"
#include "utils.hpp"
#include "condition.hpp"
namespace cxxql::expr {

template<class Cols, class Tables, class Where = empty_where>
struct select_t {
  template<class... T>
  auto where(bin_expr<T...>&& wexpr) const {
    return select_t<
      Cols,
      Tables,
      where_t<T...>
    > {
      cols,
      tables,
      where_t<T...>{std::move(wexpr)}
    };
  }
  Cols cols;
  Tables tables;
  Where cond;
};

template<class T>
auto col_to_table(const T& o) {
  if constexpr(std::is_same_v<T, std::string>) { // column specify in string, not ORM
    return dummy_table {};
  } else {
    return get_table_from_col(o);
  }
}

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
