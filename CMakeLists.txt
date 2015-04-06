cmake_minimum_required(VERSION 2.8)

project(kdtree)

set(CMAKE_MODULE_PATH ${kdtree_SOURCE_DIR}/cmake/)

find_package(Eigen2 REQUIRED)

include_directories(
	${kdtree_SOURCE_DIR}/src
	${EIGEN2_INCLUDE_DIR})

add_definitions(-O2 -ggdb)

enable_testing()
add_executable(kdtreeTest src/test/main.cpp)
target_link_libraries(kdtreeTest cpptest)
add_test(NAME kdtreeTest COMMAND kdtreeTest)

add_executable(nearest_neighbor src/examples/nearest_neighbor.cpp)
