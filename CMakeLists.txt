cmake_minimum_required(VERSION 2.8)

project(kdtree)

set(CMAKE_MODULE_PATH ${kdtree_SOURCE_DIR}/cmake/)

find_package(Eigen2 REQUIRED)

set(kdtree_sources
	KDTree.cpp
	KDNode.cpp)

include_directories(
	${kdtree_SOURCE_DIR}
	${EIGEN2_INCLUDE_DIR})

add_definitions(-ggdb)

add_library(KDTree SHARED ${kdtree_sources})

add_executable(kdtreeTest tests/main.cpp)
target_link_libraries(kdtreeTest KDTree)
