project(SingleOwner)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

find_package(Threads REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
set(SOURCE ${CMAKE_CURRENT_LIST_DIR}/source/main.cpp ${CMAKE_CURRENT_LIST_DIR}/source/provider.cpp ${CMAKE_CURRENT_LIST_DIR}/source/consumer.cpp)

include(${CMAKE_CURRENT_LIST_DIR}/../../ThreadLib/CMakeLists.txt)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../../ThreadLib/include)

add_executable(single_holder ${SOURCE})
target_link_libraries(single_holder Threads::Threads thread_lib)