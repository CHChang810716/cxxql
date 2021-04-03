#include <cxxql/to_sql.hpp>
#include <gtest/gtest.h>
#include "tab_user.hpp"
struct dummy_driver {};
TEST(to_sql_test, to_sql_str) {
  namespace ce = cxxql::expr;
  namespace cq = cxxql;
  dummy_driver dd;
  std::cout << 
    cq::to_sqlstr(
      dd,
      ce::create_table(User)
    )
  << std::endl;
}