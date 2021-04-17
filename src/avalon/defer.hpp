#pragma once
namespace avalon {

template<class Func>
struct Defer {
  ~Defer() {
    try {
      func();
    } catch(...){}
  }
  Func func;
};

template<class Func>
auto defer(Func&& func) {
  return Defer<Func> { std::forward<Func>(func) };
}
  
} // namespace avalon
