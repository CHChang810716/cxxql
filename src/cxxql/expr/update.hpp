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
template<class Table, class SetCols, class Where = empty_where>
struct update_base_t {
  Table   table;
  SetCols set_cols;
  Where   cond;
};

template<class Table, class SetCols, class Where = empty_where>
struct update_t : public update_base_t<Table, SetCols, Where> {
};

template<class Table, class SetCols>
struct update_t<Table, SetCols, empty_where> : public update_base_t<Table, SetCols, empty_where> {
  template<class... T>
  auto where(bin_expr<T...>&& wexpr) const &&{
    return update_t<
      Table,
      SetCols,
      where_t<T...>
    > {
      std::move(this->table),
      std::move(this->set_cols),
      where_t<T...>{std::move(wexpr)}
    };
  }
};


template<class Table>
struct update_pre0_t {
  template<class... Exprs>
  auto set(Exprs&&... exprs) const &&{
    // TODO: assign expression check
    auto set_cols = std::make_tuple(std::forward<Exprs>(exprs)...);
    return update_t<Table, decltype(set_cols)> {
      std::move(this->table),
      std::move(set_cols),
      empty_where {}
    };
  }

  Table table;
};

template<class Table>
auto update(const Table& table) {
  return update_pre0_t<const Table&> {table};
}
    
} // namespace cxxql::expr
