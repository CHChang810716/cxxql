#pragma once
#include <tuple>
namespace avalon::tuple {

template<class Func, class... T>
auto trans(std::tuple<T...>&& t, Func&& func) {
  return std::apply([&func](auto&&... elem){
    return std::make_tuple(func(std::move(elem))...);
  }, std::move(t));
}

template<class Func, class... T>
auto trans(const std::tuple<T...>& t, Func&& func) {
  return trans([](auto& x){ return x;}(t), std::forward<Func>(func));
}

template<class T, template<class P> class FUNC>
struct type_trans {};

template<template<class P> class FUNC, class... T>
struct type_trans<std::tuple<T...>, FUNC> {
  using type = std::tuple<FUNC<T>...>;
};

template<class T, template<class P> class FUNC>
using type_trans_t = typename type_trans<T, FUNC>::type;

}