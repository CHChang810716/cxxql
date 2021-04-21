#pragma once
#include <cstdint>
#include <cxxql/table.hpp>

struct {
  struct {
    CXXQL_COL(cxxql::integer)
    bool primary_key     = true;
    bool auto_increment  = true;
  } id;
  struct {
    CXXQL_COL(cxxql::bigint)
  } author;
  struct {
    CXXQL_COL(cxxql::varchar<255>)
    bool unique          = true;
  } title;
} Article;
CXXQL_TABLE(Article, id, author, title)