#define CXXQL_TEST
#include "tab_user.hpp"
#include "dummy_db.hpp"
#include <cxxql/exec.hpp>
#include <gtest/gtest.h>
#include <cxxql/expr.hpp>
#include <iostream>
#include <range/v3/all.hpp>
#include <gmock/gmock.h>
TEST(exec_test, select_query) {
  using ::testing::Return;
  dummy_db db;
  EXPECT_CALL(db, mock_select("SELECT User.id,User.name FROM User ;"))
    .Times(1)
    .WillOnce(Return());
  auto dset_range = cxxql::exec(
    db, 
    cxxql::expr::select(
      User.id, 
      User.name
    )
  );
  auto& range_core = dset_range.get_core();
  EXPECT_CALL(range_core, has_next())
    .Times(3)
    .WillOnce(Return(true))
    .WillOnce(Return(true))
    .WillOnce(Return(false));
  EXPECT_CALL(range_core, read())
    .Times(2)
    .WillOnce(Return(
      range_core.make_result_elem()
      .set(0, "John")
    ))
    .WillOnce(Return(
      range_core.make_result_elem()
      .set(1, "Alex")
    ));
  EXPECT_CALL(range_core, next())
    .Times(2);
  std::size_t i = 0;
  for(auto&& entry : dset_range) {
    if( i == 0 ) {
      EXPECT_EQ(entry.id, 0);
      EXPECT_EQ(entry.name, "John");
    }
    if( i == 1) {
      EXPECT_EQ(entry.id, 1);
      EXPECT_EQ(entry.name, "Alex");
    }
    i ++;
  }
}
