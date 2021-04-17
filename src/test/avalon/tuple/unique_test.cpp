#include <avalon/tuple/unique.hpp>
#include <gtest/gtest.h>
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '),...);
    std::cout << '\n';
}

TEST(avalon_tuple, utils) {
  using tup = std::tuple<int, double, int, double, double, float> ;
  using tpack = avalon::tuple::type_unique<tup>;
  using utup = typename tpack::type;
  using tup_idx = typename tpack::index;
  print_sequence(tup_idx{});
  EXPECT_TRUE((std::is_same_v<
    tup_idx, 
    std::integer_sequence<
      std::size_t, 2, 4, 5
    >
  >));
  EXPECT_EQ(std::tuple_size_v<utup>, 3);
  EXPECT_TRUE((
    std::is_same_v<
      std::tuple_element_t<0, utup>,
      int
    >
  ));
  EXPECT_TRUE((
    std::is_same_v<
      std::tuple_element_t<1, utup>,
      double
    >
  ));
  EXPECT_TRUE((
    std::is_same_v<
      std::tuple_element_t<2, utup>,
      float
    >
  ));

}