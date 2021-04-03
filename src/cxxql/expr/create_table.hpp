#pragma once

namespace cxxql::expr {

template<class Table>
struct create_table_t {
  Table table;
};

template<class Table>
auto create_table(const Table& tab) {
  return create_table_t<const Table&> {tab};
}

} // namespace cxxql::expr
