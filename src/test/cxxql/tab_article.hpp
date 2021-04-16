#pragma once
#include <cstdint>
#include <cxxql/type.hpp>
#include <cxxql/table.hpp>

struct {
  struct {
    CXXQL_COL(cxxql::bigint)
    bool is_primary      = true;
    bool auto_increment  = true;
  } id;
  struct {
    CXXQL_COL(cxxql::bigint)
    bool is_primary      = true;
    bool auto_increment  = true;
  } author;
  struct {
    CXXQL_COL(cxxql::varchar<255>)
    bool is_unique       = true;
  } title;
} Article;
CXXQL_TABLE(Article, id, author, title)