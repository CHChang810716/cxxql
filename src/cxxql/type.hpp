#pragma once
#include <string>
#include <vector>
namespace cxxql {

template<std::size_t size>
struct varchar {};
struct blob {};
using boolean = bool;
using integer = int;
using smallint = short;
using bigint = std::int64_t;
using real = double;

template<class T>
struct cxxtype {
  using type = T;
};

template<std::size_t size>
struct cxxtype<varchar<size>> {
  using type = std::string;
};

template<>
struct cxxtype<blob> {
  using type = std::vector<std::uint8_t>;
};

template<class T>
using cxxtype_t = typename cxxtype<T>::type;


}