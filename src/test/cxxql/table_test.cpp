#include <cxxql/expr/table.hpp>
#include <string>
#include <cxxql/to_sql.hpp>
#include <iostream>
#include <gtest/gtest.h>
#include "tab_user.hpp"

struct DummyEngine {};

int main() {
  // auto sql = cxxql::to_sql(
  //   DummyEngine{}, 
  //   cxxql::expr::create_table(User)
  // );
  // std::cout << sql << std::endl;
}