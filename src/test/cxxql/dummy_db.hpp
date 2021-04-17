#pragma once
#include <functional>
#include <gmock/gmock.h>

template<class MakeResultElem>
struct dummy_db_dataset_range {
  using value_type = decltype(std::declval<MakeResultElem>()());
  MOCK_METHOD(value_type, read,     (), (const));
  MOCK_METHOD(void,       next,     ());
  MOCK_METHOD(bool,       has_next, (), (const));

  std::function<value_type()> make_result_elem;
};

struct dummy_db {
  MOCK_METHOD1(mock_select, void(std::string));
  template<class MakeResultElem>
  dummy_db_dataset_range<MakeResultElem>& select(
    const std::string&  sql, 
    MakeResultElem&&    make_result_elem
  ) {
    mock_select(sql);
    static dummy_db_dataset_range<MakeResultElem> dr;
    dr.make_result_elem = std::forward<MakeResultElem>(make_result_elem);
    return dr;
  }
};