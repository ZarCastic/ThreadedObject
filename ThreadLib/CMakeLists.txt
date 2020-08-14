PROJECT(ThreadLib)

include_directories(include)
set(THREAD_LIB_SOURCES ${CMAKE_CURRENT_LIST_DIR}/source/thread_holder.cpp ${CMAKE_CURRENT_LIST_DIR}/source/thread_object.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Including ThreadLib")
add_library(thread_lib ${THREAD_LIB_SOURCES})