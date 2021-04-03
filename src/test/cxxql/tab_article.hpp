#pragma once
#include <cstdint>
#include <cxxql/type.hpp>
#include <cxxql/table.hpp>

struct {
  struct : cxxql::expr::col_design {
    using type = cxxql::bigint;
    bool is_primary     {true};
    bool auto_increment  {true};
  } id;
  struct : cxxql::expr::col_design {
    using type = cxxql::bigint;
    bool is_primary     {true};
    bool auto_increment  {true};
  } author;
  struct : cxxql::expr::col_design {
    using type = cxxql::varchar<255>;
    bool is_unique      {true};
  } title;
} Article;
CXXQL_TABLE(Article, id, author, title)