#include <cxxql/expr/select.hpp>
#include <gtest/gtest.h>
#include "../tab_user.hpp"

TEST(expr_select, select) {
  select(User.id, User.name);
}