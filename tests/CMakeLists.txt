hunter_add_package(Catch)
hunter_add_package(sqlite3)

find_package(Catch CONFIG REQUIRED)
find_package(sqlite3 CONFIG REQUIRED)

enable_testing()

add_executable(tests ${TEST_SOURCES})
target_include_directories(tests INTERFACE ${SQLITE3_INCLUDE_DIRS})
if(ENABLE_SQLCIPHER_TESTS)
    target_link_libraries(tests Catch::Catch sqlite_modern_cpp sqlite3::sqlite3 -lsqlcipher)
else()
    target_link_libraries(tests Catch::Catch sqlite_modern_cpp sqlite3::sqlite3)
endif()

catch_discover_tests(tests) 
