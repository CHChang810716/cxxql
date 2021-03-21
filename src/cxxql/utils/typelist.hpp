#pragma once
namespace cxxql::utils {

template<class... T>
struct TypeList {};

template<int i, class TL>
struct GetTypeList {};

} // namespace cxxql::utils
