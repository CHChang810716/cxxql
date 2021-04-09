#pragma once
#include <string>
#include <avalon/macro/foreach.hpp>
#include <cxxql/type.hpp>
#include <tuple>
#include <utility>
#define CXXQL_COL(t, c) \
  auto __cxxql_col(const decltype(t.c)& col) { \
    const auto& tab = t; \
    struct { \
      using cxxqltype = typename decltype(t.c)::type; \
      using cxxtype = cxxql::cxxtype_t<cxxqltype>; \
      void set_col(cxxtype&& v) { c = std::move(v); } \
      cxxtype           c; \
      const std::string __cxxql_name; \
      decltype(tab)     __cxxql_table; \
    } res {{}, #c, tab}; \
    return res; \
  }
#define CXXQL_TAB_DOT_COL(t, c)  ,t.c
#define CXXQL_TABLE(table, col0, ...) \
  auto __cxxql_table_name(const decltype(table)& t) { return #table; } \
  auto __cxxql_table_cols(const decltype(table)& t) { return std::make_tuple( \
    table.col0 AVALON_CTX_FOREACH(CXXQL_TAB_DOT_COL, table, __VA_ARGS__) \
  );} \
  CXXQL_COL(table, col0) \
  AVALON_CTX_FOREACH(CXXQL_COL, table, __VA_ARGS__)
namespace cxxql::expr {
struct col_design {};

}