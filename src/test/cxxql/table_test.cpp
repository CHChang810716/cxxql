#include <gtest/gtest.h>
#include <cxxql/table.hpp>
#include "tab_user.hpp"
#include <cxxql/expr/utils.hpp>

TEST(cxxql_expr, table_expr) {
  using namespace cxxql::expr;
  EXPECT_EQ(get_table_name(User), "User");
  EXPECT_EQ(get_col_design_name(User.id), "id");
  auto col_token = get_col_full_name(User.id);
  EXPECT_EQ(col_token.table.table_name, "User");
  EXPECT_EQ(col_token.col, "id");
  EXPECT_EQ(col_token.general_dot_format(), "User.id");

  auto cols = get_table_cols(User);
  EXPECT_EQ(get_col_name(std::get<0>(cols)), "id");
  EXPECT_EQ(get_col_name(std::get<1>(cols)), "name");
  EXPECT_TRUE(cxxql::is_col_design_v(User.id));
  EXPECT_FALSE(cxxql::is_col_design_v(0));
}