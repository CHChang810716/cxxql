#pragma once
#include <cstdint>
#include <cxxql/type.hpp>
#include <cxxql/table.hpp>

struct {
  struct : cxxql::expr::col_design {
    CXXQL_COL(cxxql::bigint)
    bool is_primary      {true};
    bool auto_increment  {true};
  } id;
  struct : cxxql::expr::col_design {
    CXXQL_COL(cxxql::varchar<255>)
    bool          is_unique      {true};
    std::string   default_value  {"John Doe"};
  } name;
} User;
CXXQL_TABLE(User, id, name)