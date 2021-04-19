#pragma once
#include <string>
#include <vector>
#include <fmt/format.h>
#include "utils.hpp"
#include "type.hpp"
#include <cxxql/expr/select.hpp>
#include "bin_expr.hpp"

namespace cxxql::to_sql_ns {

template<class Driver>
auto delete_from_(
  Driver& driver, 
  const std::string&  table,
  const std::string&  where_cond
) {
  return fmt::format(
    "DELETE FROM {}{} ;",
    table,
    where_cond
  );
}
  
} // namespace cxxql::to_sql
