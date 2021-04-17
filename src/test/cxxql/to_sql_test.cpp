#include <cxxql/to_sql.hpp>
#include <gtest/gtest.h>
#include "tab_user.hpp"
#include "tab_article.hpp"
struct dummy_driver {};
TEST(to_sql_test, create_table) {
  namespace ce = cxxql::expr;
  namespace cq = cxxql;
  dummy_driver dd;
  auto sql = cq::to_sql(
    dd,
    ce::create_table(User)
  );
  std::cout << sql << std::endl;
}
TEST(to_sql_test, select) {
  namespace ce = cxxql::expr;
  namespace cq = cxxql;
  dummy_driver dd;
  auto sql = cq::to_sql(
    dd, ce::select(User.name, Article.author).where(User.id == Article.author)
  );
  EXPECT_EQ(sql, "SELECT User.name,Article.author FROM User,Article WHERE (User.id = Article.author) ;");
}
TEST(to_sql_test, insert_into) {
  namespace ce = cxxql::expr;
  namespace cq = cxxql;
  dummy_driver dd;
  auto sql = cq::to_sql(
    dd,
    ce::insert_into(User.id, User.name).values(0, "John")
  );
  EXPECT_EQ(sql, "INSERT INTO User (id,name) VALUES (0,'John') ;");
}