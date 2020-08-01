cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(ThreadedObject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_CLANG_TIDY
#  clang-tidy-9;
#  -header-filter=.;
#  -checks=*;
#  -warnings-as-errors=*;
#)

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/source/thrad_object.cpp
)


enable_testing()
add_subdirectory(tests)
