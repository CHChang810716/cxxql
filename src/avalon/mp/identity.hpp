#pragma once
namespace avalon::mp {

template<class T>
struct identity {
  using type = T;
};

template<class T, class RT>
struct type_replace {
  using type = RT;
};
template<class T, class RT>
using type_replace_t = typename type_replace<T, RT>::type;
  
} // namespace avalon
