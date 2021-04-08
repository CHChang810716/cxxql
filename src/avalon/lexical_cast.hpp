#pragma once
#include <string>
#include <sstream>
namespace avalon {

template<class T>
auto lexical_cast(const std::string& str) {
  T o;
  std::stringstream ss;
  ss << str;
  ss >> o;
  return o;;
}

}