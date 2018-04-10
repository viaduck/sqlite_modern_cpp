cmake_minimum_required(VERSION 3.0)
OPTION(ENABLE_SQLCIPHER_TESTS "enable sqlchipher test")

# Creates the file compile_commands.json in the build directory.
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 14)

IF(HUNTER_ENABLED)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
    include("cmake/HunterGate.cmake")
    include("cmake/Catch.cmake")

    HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.19.227.tar.gz"
        SHA1 "808b778a443fcdf19c2d18fea8fa4bb59d16596a"
    )
ENDIF()

project(SqliteModernCpp)

set(TEST_SOURCE_DIR             ${CMAKE_SOURCE_DIR}/tests)
file(GLOB TEST_SOURCES          ${TEST_SOURCE_DIR}/*.cc)

IF(NOT ENABLE_SQLCIPHER_TESTS)
    list(REMOVE_ITEM TEST_SOURCES ${TEST_SOURCE_DIR}/sqlcipher.cc)
ENDIF(NOT ENABLE_SQLCIPHER_TESTS)

add_library (sqlite_modern_cpp INTERFACE)
target_include_directories(sqlite_modern_cpp INTERFACE hdr/)

IF(HUNTER_ENABLED)
    add_subdirectory(tests)
ENDIF()

# Place the file in the source directory, permitting us to place a single configuration file for YCM there.
# YCM is the code-completion engine for (neo)vim https://github.com/Valloric/YouCompleteMe
IF(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
  )
ENDIF()
