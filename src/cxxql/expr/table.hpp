#pragma once
#include <string>
#include <avalon/macro/foreach.hpp>
#include <cxxql/type.hpp>
#define CXXQL_COL(t, c) \
  auto __cxxql_col(const decltype(t.c)& col) { \
    const auto& tab = t; \
    struct { \
      using cxxtype = cxxql::cxxtype_t<decltype(t.c)::type>; \
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
struct col_design {};

}