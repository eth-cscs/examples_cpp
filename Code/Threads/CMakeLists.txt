cmake_minimum_required( VERSION 3.0.0 )

project( examples_cpp )
enable_language( CXX )


set (CMAKE_CXX_FLAGS "-std=c++14 -pthread")

FILE(GLOB_RECURSE COMMON_INC "*.hpp")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_DIR})

add_subdirectory( Intro )
add_subdirectory( DataSharing )
add_subdirectory( Synchronization )
