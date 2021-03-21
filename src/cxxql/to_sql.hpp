#pragma once
#include <string>
#include "expr/table.hpp"
namespace cxxql {

template<class Driver, class Expr>
auto to_sql(Driver&& driver, Expr&& expr) {
  // static_assert(false, "the expression connot translate to sql string");
}

// template<class Driver, class Tab>
// auto to_sql(Driver&& driver, expr::CreateTable<Tab> expr) {
//   // return driver.create_table_sql(
//   //   expr
//   // );
//   return "";
// }

}