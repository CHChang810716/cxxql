#pragma once
#include "../cxxql/tab_user.hpp"
#include "../cxxql/tab_article.hpp"
#include <cxxql.hpp>

template<class DB>
auto db_test(DB&& db) {
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
  auto&& drng = db(
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

  auto user_a = cxxql::table_var(User);
  auto article_b = cxxql::table_var(Article);
  for(auto&& entry : db(
    cxxql::select(user_a.name, article_b.title)
      .from(user_a, article_b)
      .where(user_a.id == article_b.author)
  )) {
    std::cout << entry.name << '\t' << entry.title << '\n';
  }
}