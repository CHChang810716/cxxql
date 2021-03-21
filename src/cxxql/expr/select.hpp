#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
namespace cxxql::expr {
struct empty_where {};
template<class... CondExprs>
struct where {};
template<class Cols, class Where = empty_where>
struct select_t {
  template<class... Exprs>
  auto where(Exprs... exprs) const {
    return select_t<
      Cols, 
      std::tuple<Exprs...>
    > {
      cols,
      std::move(exprs)...
    };
  }
  auto tables() const {
    return std::apply([](auto&&... col){
      std::unordered_set<std::string> cns {
        get_table_name(
          get_table_from_col(col)
        )...
      };
      return cns;
    }, cols);
  }
  Cols cols;
  Where conds;
};

template<class... RawCols>
auto select(const RawCols&... raw_cols) {
  auto tuple = std::make_tuple(__cxxql_col(raw_cols)...);
  return select_t<decltype(tuple)>{std::move(tuple), empty_where{}};
}
    
} // namespace cxxql::expr
