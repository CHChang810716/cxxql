#pragma once
namespace cxxql {

template<int size>
struct varchar {};

template<class T>
struct cxxtype {
  using type = T;
};

template<class T>
using cxxtype_t = typename cxxtype<T>::type;


}