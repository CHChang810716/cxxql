#include <cxxql/expr/select.hpp>
#include <gtest/gtest.h>
#include "../tab_user.hpp"

TEST(expr_select, select) {
  auto expr = cxxql::expr::select(User.id, User.name);
  EXPECT_EQ(cxxql::expr::get_col_name(std::get<0>(expr.cols)), "id");
  EXPECT_EQ(cxxql::expr::get_col_name(std::get<1>(expr.cols)), "name");
  EXPECT_TRUE((std::is_same_v<decltype(expr.cond), cxxql::expr::empty_where>));
  EXPECT_EQ(cxxql::expr::get_table_name(std::get<0>(expr.tables)), "User");
  auto re = expr.make_result_elem();
  re.set(42, "John");
  EXPECT_EQ(re.id, 42);
  EXPECT_EQ(re.name, "John");
  re.set_from_strs("52", "Sam");
  EXPECT_EQ(re.id, 52);
  EXPECT_EQ(re.name, "Sam");
  using result_elem_t = decltype(re);
  EXPECT_TRUE((std::is_same_v<result_elem_t::col_cxxtype<0>, std::int64_t>));
  EXPECT_TRUE((std::is_same_v<result_elem_t::col_cxxtype<1>, std::string>));
}
TEST(expr_select, select_where) {
  auto expr = cxxql::expr::select(User.id, User.name).where(User.name == "John");
  EXPECT_EQ(expr.cond.expr.oper, cxxql::expr::bin_oper::EQ);
  EXPECT_EQ(cxxql::expr::get_col_name(expr.cond.expr.left()), "name");
  EXPECT_EQ(expr.cond.expr.right(), "John");
  auto re = expr.make_result_elem();
  re.id;
  re.name;
}