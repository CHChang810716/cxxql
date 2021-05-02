#pragma once
#include "cxxql/expr.hpp"
#include "cxxql/to_sql.hpp"

namespace cxxql {

using expr::create_table;
using expr::delete_from;
using expr::drop_table;
using expr::insert_into;
using expr::select;
using expr::update;
using expr::table_var;

}

#include "cxxql/ext.hpp"
#include "cxxql/db.hpp"