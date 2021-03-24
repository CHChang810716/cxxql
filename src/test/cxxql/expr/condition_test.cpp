#include <gtest/gtest.h>
#include "../tab_user.hpp"
#include "../tab_article.hpp"
#include <cxxql/expr/condition.hpp>

TEST(expr_condition, condition) {
  EXPECT_TRUE(1 == 1);
  EXPECT_FALSE(1 == 2);
  EXPECT_TRUE((std::is_convertible_v<decltype(User.id), cxxql::expr::col_design>));
  EXPECT_FALSE((std::is_convertible_v<bool, cxxql::expr::col_design>));
  EXPECT_FALSE((cxxql::expr::is_bin_expr_v<bool>));
  EXPECT_FALSE(cxxql::expr::is_bin_expr_v<int>);
  auto bexpr0 = User.id == Article.id;
  auto bexpr1 = User.id == 0;
  auto bexpr2 = ("asdf" == User.id) && (Article.id != 0);
  EXPECT_TRUE(cxxql::expr::is_bin_expr_v<decltype(bexpr0)>);
  EXPECT_TRUE(cxxql::expr::is_bin_expr_v<decltype(bexpr1)>);
  EXPECT_TRUE(cxxql::expr::is_bin_expr_v<decltype(bexpr2)>);

  EXPECT_EQ(bexpr2.oper, cxxql::expr::cond_oper::AND);
  EXPECT_EQ(bexpr2.left().oper, cxxql::expr::cond_oper::EQ);
  EXPECT_EQ(bexpr2.left().left(), "asdf");
  EXPECT_EQ(cxxql::expr::get_col_full_name(bexpr2.left().right()), "User.id");
  EXPECT_EQ(bexpr2.right().oper, cxxql::expr::cond_oper::NE);
  EXPECT_EQ(cxxql::expr::get_col_full_name(bexpr2.right().left()), "Article.id" );
  EXPECT_EQ(bexpr2.right().right(), 0);

}