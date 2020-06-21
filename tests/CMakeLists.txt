cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


include_directories(../include)
include_directories(./)
set(SOURCES ../source/thread_object.cpp)

set(TEST_SOURCES main_tests.cpp
thread_object_test.cpp
)
add_executable(test.bin ${SOURCES} ${TEST_SOURCES})
target_link_libraries(test.bin ${GTEST_LIBRARIES} Threads::Threads)