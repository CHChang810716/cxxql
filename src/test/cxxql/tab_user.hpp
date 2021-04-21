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
    CXXQL_COL(cxxql::varchar<255>)
    bool          not_null       = true;
    bool          unique         = true;
    std::string   default_value  = "John Doe";
  } name;
} User;
CXXQL_TABLE(User, id, name)