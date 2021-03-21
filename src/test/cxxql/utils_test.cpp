#include <avalon/macro/foreach.hpp>
#include <gtest/gtest.h>

#define XSTR(s) #s
TEST(utils_test, macro_foreach) {
  std::cout << AVALON_FOREACH(XSTR, a, b, c) << std::endl;
}