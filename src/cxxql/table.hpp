#pragma once
#include <string>
#include <avalon/macro/foreach.hpp>
#include <cxxql/type.hpp>
#include <tuple>
#include <utility>
#include <cxxql/expr/col_design.hpp>
#include <cxxql/expr/bin_expr.hpp>
#include <avalon/tuple.hpp>
#define CXXQL_COL_FUNC(t, c) \
  auto __cxxql_col(const decltype(t.c)& col) { \
    const auto& tab = t; \
    struct { \
      using design_t = decltype(t.c); \
      using cxxqltype = typename design_t::type; \
      using cxxtype = cxxql::cxxtype_t<cxxqltype>; \
      void set_col(cxxtype&& v) { c = std::move(v); } \
      cxxtype&        get_col() { return c; } \
      const cxxtype&  get_col() const { return c; } \
      cxxtype           c; \
      const std::string __cxxql_name; \
      const auto& __cxxql_table() const { return t; } \
      const auto& __cxxql_col_design() const { return t.c; } \
    } res {{}, #c}; \
    return res; \
  }
#define CXXQL_TAB_DOT_COL(t, c)  ,t.c
#define CXXQL_TABLE(table, col0, ...) \
  auto __cxxql_table_name(const decltype(table)& t) { return #table; } \
  auto __cxxql_table_cols(decltype(table)& t) { return avalon::make_tuple( \
    t.col0 AVALON_CTX_FOREACH(CXXQL_TAB_DOT_COL, t, __VA_ARGS__) \
  );} \
  auto __cxxql_table_cols(const decltype(table)& t) { return avalon::make_tuple( \
    t.col0 AVALON_CTX_FOREACH(CXXQL_TAB_DOT_COL, t, __VA_ARGS__) \
  );} \
  CXXQL_COL_FUNC(table, col0) \
  AVALON_CTX_FOREACH(CXXQL_COL_FUNC, table, __VA_ARGS__)

#define CXXQL_COL(t) \
  using type = t; \
  bool __cxxql_col_test; \
  CXXQL_EXPR_BOP_MEM(=, cxxql::expr::bin_oper::ASN) \
  bool is_table_var() const { return !table_var_name_.empty(); } \
  const std::string& table_var_name() const { return table_var_name_; } \
  template<class Str> void set_table_var_name(Str&& str) {table_var_name_ = std::forward<Str>(str);} \
  private: std::string table_var_name_; \
  public:

/*
#define CXXQL_COL(t) \
  using type = t; \
  bool __cxxql_col_test; \
  CXXQL_EXPR_BOP_MEM(=, cxxql::expr::bin_oper::ASN)
*/
