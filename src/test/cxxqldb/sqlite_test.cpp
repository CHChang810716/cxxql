#include <gtest/gtest.h>
#include "../cxxql/tab_user.hpp"
#include "../cxxql/tab_article.hpp"
#include <cxxqldb/sqlite.hpp>
struct {
  const char* file_path = "test_sqlite.db";
} sqlite_config;
TEST(sqlite, all) {
  auto db = cxxqldb::sqlite::make_db(sqlite_config);
  db(cxxql::drop_table_if_exists(User));
  db(cxxql::drop_table_if_exists(Article));
  db(cxxql::create_table(User));
  db(cxxql::create_table(Article));
  db(cxxql::insert_into(User.name).values("John"));
  db(cxxql::insert_into(User.name).values("Candy"));
  db(cxxql::insert_into(User.name).values("Alex"));
  db(cxxql::insert_into(Article.author, Article.title)
    .values(1, "My blog"));
  db(cxxql::insert_into(Article.author, Article.title)
    .values(1, "John's Work"));
  db(cxxql::insert_into(Article.author, Article.title)
    .values(3, "Alex's TODO"));
  auto drng = db(
    cxxql::select(User.name, Article.title)
      .where(User.id == Article.author)
  );
  std::size_t i = 0;
  for(auto&& entry : drng) {
    if(entry.title == "John's Work") {
      EXPECT_EQ(entry.name, "John");
    }
    if(entry.title == "My blog") {
      EXPECT_EQ(entry.name, "John");
    }
    if(entry.title == "Alex's TODO") {
      EXPECT_EQ(entry.name, "Alex");
    }
    i ++;
  }
  EXPECT_EQ(i, 3);
  db(cxxql::update(User).set(User.name = "Frank").where(User.id == 1));
  i = 0;
  for(auto&& entry : db(cxxql::select(User.name).where(User.id == 1))) {
    EXPECT_EQ(entry.name, "Frank");
    i++;
  }
  EXPECT_EQ(i, 1);
  db(cxxql::delete_from(User).where(User.id == 1));
  i = 0;
  for(auto&& entry : db(cxxql::select(User.name).where(User.id == 1))) {
    i++;
  }
  EXPECT_EQ(i, 0);

}