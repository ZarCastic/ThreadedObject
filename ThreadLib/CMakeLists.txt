PROJECT(ThreadLib)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
set(THREAD_LIB_SOURCES ${CMAKE_CURRENT_LIST_DIR}/source/thread_holder.cpp ${CMAKE_CURRENT_LIST_DIR}/source/thread_object.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT THREAD_LIB_BUILD)
    set(THREAD_LIB_BUILD true)
    add_library(thread_lib ${THREAD_LIB_SOURCES})
endif ()