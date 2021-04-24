#include <cxxqldb/postgresql.hpp>
#include <gtest/gtest.h>
#include "common_test.h"

TEST(postgresql, all) {
  cxxqldb::postgresql::config config;
  config.dbname   = "testdb"  ;
  config.host     = "localhost"  ;
  config.user     = "johnidfet"  ;
  config.password = "qsefthuk90"  ;

  auto db = cxxqldb::postgresql::make_db(std::move(config));
  db.dbglog = [](const auto& str) {
    std::cout << str << std::endl;
  };
  db_test(db);
}