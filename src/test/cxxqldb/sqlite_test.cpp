#include <gtest/gtest.h>
#include <cxxqldb/sqlite.hpp>
#include "common_test.h"
struct {
  const char* file_path = "test_sqlite.db";
} sqlite_config;
TEST(sqlite, all) {
  auto db = cxxqldb::sqlite::make_db(sqlite_config);
  db_test(db);
}