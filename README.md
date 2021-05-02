[![appveyor](https://ci.appveyor.com/api/projects/status/ygi0nxl64khq6ipg/branch/master?svg=true)](https://ci.appveyor.com/project/CHChang810716/cxxql/branch/master)
![github workflow](https://github.com/CHChang810716/cxxql/actions/workflows/cmake.yml/badge.svg)

# Intro

This is a light weight C++ to SQL bridge library, includes connector and ORM-like wrapper.

This project is largly inspired from rbock/sqlpp17 and attempt to improve the structure syntax and specific DB query generation.

# A Quick look

Table schema
```c++
// tab_user.hpp
#pragma once
#include <cstdint>
#include <cxxql/table.hpp>

struct {
  struct {
    CXXQL_COL(cxxql::integer)
    bool primary_key     = true;
    bool auto_increment  = true;
  } id;
  struct {
    CXXQL_COL(cxxql::varchar<255>)
    bool          not_null       = true;
    bool          unique         = true;
    std::string   default_value  = "John Doe";
  } name;
} User;
CXXQL_TABLE(User, id, name)
```
```c++
// tab_article.hpp
#pragma once
#include <cstdint>
#include <cxxql/table.hpp>

struct {
  struct {
    CXXQL_COL(cxxql::integer)
    bool primary_key     = true;
    bool auto_increment  = true;
  } id;
  struct {
    CXXQL_COL(cxxql::bigint)
  } author;
  struct {
    CXXQL_COL(cxxql::varchar<255>)
    bool unique          = true;
  } title;
} Article;
CXXQL_TABLE(Article, id, author, title)
```

CRUD operations
```c++
#include <cxxqldb/postgresql.hpp>
int main() {
  cxxqldb::postgresql::config config;
  config.dbname   = "testdb"      ;
  config.host     = "localhost"   ;
  config.user     = "testuser"    ;
  config.password = "qsefthuk90"  ;

  auto db = cxxqldb::postgresql::make_db(std::move(config));
  db(cxxql::drop_table_if_exists(User));
  db(cxxql::drop_table_if_exists(Article));
  db(cxxql::create_table(User));
  db(cxxql::create_table(Article));
  db(cxxql::insert_into(User.name).values("John"));
  db(cxxql::insert_into(User.name).values("Candy"));
  db(cxxql::insert_into(User.name).values("Alex"));
  db(cxxql::insert_into(Article.author, Article.title)
    .values(1, "My blog"));
  db(cxxql::insert_into(Article.author, Article.title)
    .values(1, "John's Work"));
  db(cxxql::insert_into(Article.author, Article.title)
    .values(3, "Alex's TODO"));
  for(auto&& entry : db(
    cxxql::select(User.name, Article.title)
      .where(User.id == Article.author)
  )) {
    std::cout << entry.name << '\t' << entry.title << std::endl;
  }
}
```

# Build Project

## Recommended environments

* g++ >= 7.3
* CMake >= 3.13
* Linux, Windows is tested (see CI tag)
* On Windows, mingw is recommended

## Steps

```bash
>cd 
>mkdir build
>cd build
>cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../stage -DBUILD_TEST=ON
# build with 4 core
>cmake --build . --target install -j 4
# run test
>ctest
```

# Use Package

## With Hunter Package manager

This project is using CMake Hunter to maintain 3rd party, but not yet register to official Hunter site.

Therefore, use Hunter submodule solution to link this package is recommended, see [here](https://hunter.readthedocs.io/en/latest/user-guides/hunter-user/git-submodule.html) for more details.

## Manually (just like all CMake package)

The install build will generate capable CMake config script, 
use cmake find_package syntax and identify the the CMake config script location is also a proper way to use this cmake project.

[This CMake offical page](https://cmake.org/cmake/help/latest/command/find_package.html) should help.


# Reference

[rbock/sqlpp17](https://github.com/rbock/sqlpp17)
