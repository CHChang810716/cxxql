#include <cxxql/expr/table.hpp>
#include <cstdint>
#include <string>
#include <cxxql/to_sql.hpp>
#include <cxxql/type.hpp>
constexpr struct {
    struct {
        using type = std::uint64_t;
        static constexpr bool is_primary = true;
        static constexpr bool auto_incrment = true;
    } id;
    struct {
        using type = cxxql::varchar<255>;
        static constexpr bool is_unique = true;
    } name;
} User;

struct DummyEngine {};

int main() {
    auto sql = cxxql::to_sql(cxxql::expr::create_table(User));
}