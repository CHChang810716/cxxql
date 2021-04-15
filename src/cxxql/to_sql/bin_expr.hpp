#pragma once
#include <string>
#include <cxxql/expr/bin_expr.hpp>
#include <fmt/format.h>
namespace cxxql::to_sql_ns {

std::string bin_oper(const expr::bin_oper::type& op) {
  namespace ce = cxxql::expr;
  switch(op) {
    case ce::bin_oper::EQ:  return "=";
    case ce::bin_oper::NE:  return "<>";
    case ce::bin_oper::GT:  return ">";
    case ce::bin_oper::GE:  return ">=";
    case ce::bin_oper::LT:  return "<";
    case ce::bin_oper::LE:  return "<=";
    case ce::bin_oper::OR:  return "OR";
    case ce::bin_oper::AND: return "AND";
    case ce::bin_oper::ASN: return "=";
    default:
      throw std::runtime_error(fmt::format("BUG: bin oper {} unable to convert to string", op));
  }
}
// template<class ColDesign>
// std::enable_if_t<
//   cxxql::is_col_design_type_v<ColDesign>,
//   std::string
// > bin_expr(const ColDesign& cd) {
//   return cxxql::
// }
template<class T>
std::string bin_expr(const T& expr) {
  if constexpr(expr::is_bin_expr_v<T>) {
    return fmt::format("({} {} {})", 
      bin_expr(expr.left()),
      bin_oper(expr.oper),
      bin_expr(expr.right())
    );
  } else if constexpr(is_col_design_type_v<T>) {
    return expr::get_col_full_name(expr);
  } else {
    return fmt::format("{}", expr);
  }
}

}