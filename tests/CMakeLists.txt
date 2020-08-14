PROJECT(ThreadingLib_Tests)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(../ThreadLib/CMakeLists.txt)
include_directories(../ThreadLib/include)

include(../cmake/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/../cmake
        ${PROJECT_BINARY_DIR}/googletest
)
enable_testing()

set(TEST_SOURCES ${CMAKE_CURRENT_LIST_DIR}/main_tests.cpp
        ${CMAKE_CURRENT_LIST_DIR}/thread_object_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/thread_holder_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/test_util/util.cpp)
add_executable(unit_tests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(unit_tests gtest_main Threads::Threads thread_lib)

add_test(
        NAME
        unit
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
