# Ares "CMakeLists"
# Required to build a make file

cmake_minimum_required(VERSION 2.8)
project(Ares)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wno-maybe-uninitialized -Wno-unused-result -O3")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++")

file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
add_library(Ares SHARED ${SOURCE_FILES})
target_link_libraries(Ares SDL2 GL dl)
