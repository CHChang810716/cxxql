if(USE_SQLITE)
  include(cmake/scheme/test.cmake)
  target_link_libraries(${AKT_TARGET} PRIVATE sqlite3::sqlite3)
endif()