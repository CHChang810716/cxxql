#include <gtest/gtest.h>
#include <cxxql/expr/table.hpp>
#include "../tab_user.hpp"

TEST(cxxql_expr, table_expr) {
  EXPECT_EQ(cxxql::expr::get_table_name(User), "User");
  EXPECT_EQ(cxxql::expr::get_col_name(User.id), "id");
  EXPECT_EQ(cxxql::expr::get_col_full_name(User.id), "User.id");
}