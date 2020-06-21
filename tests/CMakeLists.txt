set(SOURCES ../source/thread_object.cpp)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(TEST_SOURCES main_tests.cpp
thread_object_test.cpp
)
add_executable(unit_tests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(unit_tests gtest_main Threads::Threads)

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
