#pragma once
#include <range/v3/view/facade.hpp>
#include <optional>
namespace cxxql::exec_ns {

template<class T>
struct any_mem_holder {
  using type = T;
};

template<class T>
struct any_mem_holder<T&> {
  using type = std::optional<std::reference_wrapper<T>>;
};

template<class T>
using any_mem_holder_t = typename any_mem_holder<T>::type;

template<class Core>
struct dataset_range : public ranges::view_facade<
  dataset_range<Core>,
  ranges::cardinality::infinite
> {
  friend ranges::range_access;
  using this_t      = dataset_range<Core>;
  using core_t      = std::remove_reference_t<Core>;
  using base_t      = ranges::view_facade<dataset_range<Core>>;
  using value_type  = typename core_t::value_type;

  template<class T>
  dataset_range(T&& core)
  : core_(std::forward<T>(core))
  {}
  dataset_range() = default;
  value_type read() const {
    return get_core().read();
  }
  bool equal(ranges::default_sentinel_t) const {
    return !get_core().has_next();
  }
  void next() {
    get_core().next();
  }

#ifdef CXXQL_TEST
public:
#else
private:
#endif
  core_t& get_core() {
    if constexpr(std::is_reference_v<Core>) {
      return core_.value().get();
    } else {
      return core_;
    }
  }
  const core_t& get_core() const {
    return const_cast<this_t&>(*this).get_core();
  }
private:
  any_mem_holder_t<Core> core_;
};
template<class Core>
auto make_dataset_range(Core&& core) {
  return dataset_range<Core>{std::forward<Core>(core)};
}

}