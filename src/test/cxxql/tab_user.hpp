#pragma once
#include <cstdint>
#include <cxxql/type.hpp>
#include <cxxql/expr/table.hpp>

struct {
  struct : cxxql::expr::col_design {
    using type = std::uint64_t;
    bool is_primary     {true};
    bool auto_increment  {true};
  } id;
  struct : cxxql::expr::col_design {
    using type = cxxql::varchar<255>;
    bool is_unique      {true};
  } name;
} User;
CXXQL_TABLE(User, id, name)