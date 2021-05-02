#pragma once
#include <string>
#include <random>
#include <set>
#include <avalon/tuple/trans.hpp>

namespace cxxql::expr {

std::string make_random_symbol(std::size_t n) {
  static std::set<std::string> pool;
  static std::string charset = [](){
    std::string res;
    for(char c = 'a'; c <= 'z'; c++) {
      res.push_back(c);
    }
    for(char c = 'A'; c <= 'Z'; c++) {
      res.push_back(c);
    }
    // for(char c = '0'; c <= '9'; c++) {
    //   res.push_back(c);
    // }
    return res;
  }();
  static std::default_random_engine gen;
  static std::uniform_int_distribution<std::size_t> dist(
    std::size_t(0), charset.size() - 1
  );
  std::string res;
  do {
    res.clear();
    for(std::size_t i = 0; i < n; i ++) {
      res.push_back(charset[dist(gen)]);
    }
  } while(pool.count(res) != 0);
  pool.emplace(res);
  return res;
}

template<class Table>
struct table_var_t : Table{
  using table_t = Table;
  std::string symbol;
};
template<class Table>
auto table_var(const Table& tab, const std::string& symbol) {
  table_var_t<Table> res{tab, std::move(symbol)};
  auto&& cols = __cxxql_table_cols(res);
  std::apply([&symbol](auto&&... c){
    auto list = {
      (c.set_table_var_name(symbol), 0)...
    };
    return 0;
  }, cols);
  return res;
}
template<class Table>
auto table_var(const Table& tab) {
  auto symbol = make_random_symbol(4);
  return table_var(tab, symbol);
}

// template<class Table>
// struct is_table_var : public std::false_type {};
// 
// template<class Table>
// struct is_table_var<table_var_t<Table>> : public std::true_type {};
// 
// template<class Table>
// constexpr bool is_table_var_v = is_table_var<Table>::value;

} // namespace cxxql::expr
