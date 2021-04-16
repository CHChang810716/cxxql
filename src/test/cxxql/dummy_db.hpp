#pragma once
#include <functional>
#include <gmock/gmock.h>

template<class MakeResultElem>
struct dummy_db_dataset_range {
  using result_elem_t = decltype(std::declval<MakeResultElem>()());
  MOCK_METHOD(result_elem_t, read, (), (const));
  MOCK_METHOD(void, next, ());
  MOCK_METHOD(bool, has_next, (), (const));
};

struct dummy_db {
  MOCK_METHOD1(mock_select, void(std::string));
  template<class MakeResultElem>
  dummy_db_dataset_range<MakeResultElem> select(const std::string& sql, MakeResultElem&& make_result_elem) {
    mock_select(sql);
    dummy_db_dataset_range<MakeResultElem> dr;
    // return dr;
  }
};