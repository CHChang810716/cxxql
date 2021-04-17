#include <cxxqldb/sqlite.hpp>
#include <gtest/gtest.h>
#include <cxxql/expr.hpp>
#include "../cxxql/tab_user.hpp"
#include "../cxxql/tab_article.hpp"
#include <experimental/filesystem>
struct {
  const char* file_path = "test_sqlite.db";
} sqlite_config;
TEST(sqlite, select) {
  namespace ce = cxxql::expr;
  std::remove(sqlite_config.file_path);

  cxxqldb::sqlite::db db(sqlite_config);
  db(ce::create_table(User));
  db(ce::create_table(Article));
  db(ce::insert_into(User.id, User.name).values(0, "John"));
  db(ce::insert_into(User.id, User.name).values(1, "Candy"));
  db(ce::insert_into(User.id, User.name).values(2, "Alex"));
  db(ce::insert_into(Article.id, Article.author, Article.title)
    .values(0, 0, "My blog"));
  db(ce::insert_into(Article.id, Article.author, Article.title)
    .values(1, 0, "John's Work"));
  db(ce::insert_into(Article.id, Article.author, Article.title)
    .values(2, 2, "Alex's TODO"));
  auto drng = db(
    ce::select(User.name, Article.title)
      .where(User.id == Article.author)
  );
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
  }
}