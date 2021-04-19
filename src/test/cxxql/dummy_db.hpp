#pragma once
#include <functional>
#include <gmock/gmock.h>

template<class ResultElem>
struct dummy_db_dataset_range {
  using value_type = ResultElem;
  MOCK_METHOD(value_type, read,     (), (const));
  MOCK_METHOD(void,       next,     ());
  MOCK_METHOD(bool,       has_next, (), (const));
  auto make_result_elem() {
    return ResultElem();
  }
};

struct dummy_db {
  MOCK_METHOD1(mock_select, void(std::string));
  template<class ResultElem>
  dummy_db_dataset_range<ResultElem>& select(
    const std::string&  sql
  ) {
    mock_select(sql);
    static dummy_db_dataset_range<ResultElem> dr;
    return dr;
  }
};
#include <cxxql/to_sql.hpp>