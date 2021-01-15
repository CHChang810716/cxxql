#pragma once
#include <string>
namespace cxxql {

template<class Expr>
std::string to_sql(Expr&& expr) {
    static_assert(false, "the expression connot translate to sql string");
}

}