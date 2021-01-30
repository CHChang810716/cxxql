#pragma once
#include <string>
namespace cxxql {

template<class Driver, class Expr>
std::string to_sql(Driver&& driver, Expr&& expr) {
    static_assert(false, "the expression connot translate to sql string");
}

}