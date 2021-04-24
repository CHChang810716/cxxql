include(cmake/scheme/test.cmake)
target_link_libraries(${AKT_TARGET} PRIVATE PostgreSQL::libpq)