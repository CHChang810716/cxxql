#pragma once
namespace cxxql::expr {

template<class Table>
struct drop_table_t {
  Table table;
};

template<class Table>
auto drop_table(const Table& tab) {
  return drop_table_t<const Table&> {tab};
}
  
} // namespace cxxql::expr
