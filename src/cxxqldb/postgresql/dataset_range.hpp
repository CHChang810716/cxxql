#pragma once
#include <libpq-fe.h>
#include <avalon/lexical_cast.hpp>
#include <avalon/mp/identity.hpp>
#include "utils.hpp"

namespace cxxqldb::postgresql {

template<class ResultElem>
struct dataset_range {
  using value_type = ResultElem;
  template<class T>
  using tid = avalon::mp::identity<T>;

  dataset_range(result_ptr sel_res) {
    pg_res_ = std::move(sel_res);
    rows_ = PQntuples(pg_res_.get());
    row_i_ = 0;
  }

  dataset_range() = default;
  
  value_type read() const{
    ResultElem res_elem;
    set_re(res_elem, std::make_integer_sequence<int, value_type::col_num>{});
    return res_elem;
  }
  void next() { row_i_ ++; }

  bool has_next() const {
    return row_i_ < rows_;
  }
  
private:
  template<int i>
  auto col_v() const {
    using cxxtype = typename value_type::template col_cxxtype<i>;
    auto value = avalon::lexical_cast<cxxtype>(
      PQgetvalue(pg_res_.get(), row_i_, i)
    );
    return value;
  }

  template<class Int, Int... i>
  void set_re(value_type& re, std::integer_sequence<Int, i...> is) const {
    re.set(col_v<i>()...);
  }

  result_ptr  pg_res_       {nullptr, result_deletor{}};
  int         rows_         {-1};
  int         row_i_        {-1};
};

}