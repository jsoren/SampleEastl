cmake_minimum_required(VERSION 3.14)
project(SampleEastl)

set(CMAKE_CXX_STANDARD 14)

SET(EASTL_BUILD_TESTS true) # Needed for some includes

add_subdirectory(EASTL)

add_executable(SampleEastl main.cpp eastl_allocator_impl.cpp)

target_link_libraries(SampleEastl LINK_PUBLIC EASTL)