#include <gtest/gtest.h>
#include <cxxql/to_sql/utils.hpp>
using namespace std::string_literals;
using namespace cxxql::to_sql_ns;
TEST(cxxql_to_sql, utils) {
  // EXPECT_EQ(append("a"s, "s"s, "asdf"s), "asasdf");
  EXPECT_EQ(
    args_to_string(","s, "aaa"s, "bbb"s, "ccc"s),
    "aaa,bbb,ccc"
  );
  EXPECT_EQ(
    args_to_string(","s),
    ""
  );
  EXPECT_EQ(
    args_to_string(","s, "aaa"s),
    "aaa"
  );
  EXPECT_EQ(
    tuple_to_string(
      ",", 
      std::make_tuple("aaa"s, "bbb"s, "ccc"s)
    ),
    "aaa,bbb,ccc"
  );
  EXPECT_EQ(
    tuple_to_string(
      ",", 
      std::make_tuple()
    ),
    ""
  );
  EXPECT_EQ(
    tuple_to_string(
      ",", 
      std::make_tuple("aaa"s)
    ),
    "aaa"
  );
}