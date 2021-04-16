#pragma once
#include <range/v3/view/facade.hpp>
namespace cxxql::exec_ns {

template<class Core>
struct dataset_range : public ranges::view_facade<
  dataset_range<Core>
> {
  friend ranges::range_access;
  using base_t = ranges::view_facade<
    dataset_range<Core>
  >;
  template<class T>
  dataset_range(T&& core)
  : base_t()
  , core_(std::forward<T>(core))
  {}

  auto read() const {
    return core_.read();
  }
  bool equal(ranges::default_sentinel_t) const {
    return !core_.has_next();
  }
  void next() {
    core_.next();
  }
#ifdef CXXQL_TEST
  Core& get_core() {
    return core_;
  }
#endif
private:
  Core core_;
};
template<class Core>
auto make_dataset_range(Core&& core) {
  return dataset_range<Core>(std::forward<Core>(core));
}

}