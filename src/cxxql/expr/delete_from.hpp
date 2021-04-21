#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>
#include "utils.hpp"
#include "condition.hpp"
namespace cxxql::expr {


template<class Table, class Where = empty_where>
struct delete_from_base_t {
  Table   table;
  Where   cond;
};

template<class Table, class Where = empty_where>
struct delete_from_t : public delete_from_base_t<Table, Where> {
  template<class... T>
  auto where(bin_expr<T...>&& wexpr) const &&{
    if constexpr(std::is_same_v<Where, empty_where>) {
      return delete_from_t<
        Table,
        where_t<T...>
      > {
        this->table,
        where_t<T...>{std::move(wexpr)}
      };
    }
  }
};


template<class Table>
auto delete_from(const Table& table) {
  return delete_from_t<const Table&, empty_where>{
    table,
    empty_where{}
  };
}
    
} // namespace cxxql::expr
