#pragma once
#include <string>
#include <fmt/format.h>
#include <avalon/tuple.hpp>
#include "utils.hpp"
namespace cxxql::to_sql_ns {

template<class Driver, class Cols, class Table, class Values>
std::string insert_into(
  Driver& driver,
  const Cols& cols,
  const Table& table,
  const Values& values
) {
  return fmt::format("INSERT INTO {} ({}) VALUES ({}) ;",
    table, 
    tuple_to_string(",", cols),
    tuple_to_string(",", values)
  );
}
  
} // namespace cxxql::to_sql
