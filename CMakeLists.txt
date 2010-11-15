cmake_minimum_required(VERSION 2.8)

project(kdtree)

set(CMAKE_MODULE_PATH ${kdtree_SOURCE_DIR}/cmake/)

find_package(Eigen2 REQUIRED)

include_directories(
	${kdtree_SOURCE_DIR}
	${EIGEN2_INCLUDE_DIR})

add_definitions(-O2 -ggdb)

add_executable(kdtreeTest tests/main.cpp)
