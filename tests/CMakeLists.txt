set(SOURCES 
  ../source/thread_object.cpp
  ../source/thread_holder.cpp
)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(TEST_SOURCES main_tests.cpp
        thread_object_test.cpp
        thread_holder_test.cpp
        test_util/util.cpp ThreadedObject.cpp ThreadedObject.h)
add_executable(unit_tests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(unit_tests gtest_main Threads::Threads)

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
