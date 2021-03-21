#pragma once
#include <string>
#include <avalon/macro/foreach.hpp>
#include <cxxql/type.hpp>
#define CXXQL_COL(t, c) \
  auto __cxxql_col(const decltype(t.c)& col) { \
    const auto& tab = t; \
    using cxxtype = cxxql::cxxtype_t<decltype(t.c)::type>; \
    struct { \
      cxxtype           c; \
      const std::string __cxxql_name; \
      decltype(tab)     __cxxql_table; \
    } res {{}, #c, tab}; \
    return res; \
  }
#define CXXQL_TABLE(table, ...) \
  auto __cxxql_table_name(const decltype(table)& t) { return #table; } \
  AVALON_CTX_FOREACH(CXXQL_COL, table, __VA_ARGS__)

namespace cxxql::expr {

template<class Tab>
auto get_table_name(const Tab& tab) {
  return __cxxql_table_name(tab);
}

template<class ColDng>
auto get_col_name(const ColDng& col_dng) {
  return __cxxql_col(col_dng).__cxxql_name;
}

template<class ColDng>
auto get_col_full_name(const ColDng& col_dng) {
  auto col = __cxxql_col(col_dng);
  return get_table_name(col.__cxxql_table) + ("." + col.__cxxql_name);
}

}