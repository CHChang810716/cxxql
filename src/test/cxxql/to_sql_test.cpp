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
TEST(to_sql_test, drop_table) {
  namespace ce = cxxql::expr;
  namespace cq = cxxql;
  dummy_driver dd;
  auto sql = cq::to_sql(
    dd, ce::drop_table(User)
  );
  EXPECT_EQ(sql, "DROP TABLE User ;");
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

TEST(to_sql_test, update) {
  namespace ce = cxxql::expr;
  namespace cq = cxxql;
  dummy_driver dd;
  auto sql = cq::to_sql(
    dd,
    ce::update(User).set(User.id = 0, User.name = "John").where(User.id == 1)
  );
  EXPECT_EQ(sql, "UPDATE User SET User.id = 0,User.name = 'John' WHERE (User.id = 1) ;");
  
}