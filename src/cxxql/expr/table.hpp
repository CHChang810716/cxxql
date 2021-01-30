#pragma once

namespace cxxql::expr {

// struct ColDef {
//     constexpr ColDef(const char* str) 
//     : data(str)
//     {}
// 
//     const char* data;
// };
// 
// struct Table {
// };

template<class Tab>
struct CreateTable {
    Tab table;
};

template<class Tab>
constexpr auto create_table(Tab tab) {
    return CreateTable<Tab>{tab};
}

}