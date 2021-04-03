#include <cxxql/expr/insert_into.hpp>
#include <gtest/gtest.h>
#include "../tab_user.hpp"

TEST(expr_insert, insert) {
  namespace ce = cxxql::expr;
  auto expr = cxxql::expr::insert_into(
    User.id, User.name
  ).values(42, "John");
  EXPECT_EQ(ce::get_table_name(expr.table), "User");
  EXPECT_EQ(ce::get_col_name(std::get<0>(expr.cols)), "id");
  EXPECT_EQ(ce::get_col_name(std::get<1>(expr.cols)), "name");
  EXPECT_EQ(std::get<0>(expr.col_values), 42);
  EXPECT_EQ(std::get<1>(expr.col_values), "John");
}