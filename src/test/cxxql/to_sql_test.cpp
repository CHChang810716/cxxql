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
  std::cout << sql << std::endl;
  EXPECT_EQ(sql, "UPDATE User SET id = 0,name = 'John' WHERE (User.id = 1) ;");
}
TEST(to_sql_test, delete_from) {
  namespace ce = cxxql::expr;
  namespace cq = cxxql;
  dummy_driver dd;
  auto sql = cq::to_sql(
    dd,
    ce::delete_from(User).where(User.id == 1)
  );
  std::cout << sql << std::endl;
  EXPECT_EQ(sql, "DELETE FROM User WHERE (User.id = 1) ;");
  
}
auto __cxxql_table_cols2(const decltype(User)& t) {
  return avalon::make_tuple(t.id, t.name);
}
auto __cxxql_table_cols2(decltype(User)& t) {
  return avalon::make_tuple(t.id, t.name);
}
TEST(to_sql_test, select_table_var) {
  namespace ce = cxxql::expr;
  namespace cq = cxxql;
  dummy_driver dd;
  auto ua = cxxql::expr::table_var(User, "a");
  auto ab = cxxql::expr::table_var(Article, "b");
  // std::cout << ua.id.table_var_name() << std::endl;
  auto sql = cq::to_sql(
    dd, ce::select(ua.name, ab.author).from(ua, ab).where(ua.id == ab.author)
  );
  std::cout << sql << std::endl;
  EXPECT_EQ(sql, "SELECT a.name,b.author FROM User a,Article b WHERE (a.id = b.author) ;");
}