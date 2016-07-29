cmake_minimum_required( VERSION 3.0.0 )

project( examples_cpp )
enable_language( CXX )


find_package( Boost COMPONENTS program_options REQUIRED )

include_directories( SYSTEM ${Boost_INCLUDE_DIRS} )
link_directories( ${Boost_LIBRARY_DIRS} )
set (CMAKE_CXX_FLAGS "-std=c++14")

FILE(GLOB_RECURSE COMMON_INC "*.hpp")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_DIR})

add_subdirectory( CRTP )
#add_subdirectory( CountDigits ) # depends on boost::program_options
add_subdirectory( ET )
#add_subdirectory( Extents ) # depends on boost::program_options
add_subdirectory( Lambdas )
add_subdirectory( Packs )
add_subdirectory( Partial_Specialization )
add_subdirectory( Proxy )
#add_subdirectory( SmartPointers )
add_subdirectory( Storage )
add_subdirectory( Templates )
add_subdirectory( TemplateMetaProgramming )
add_subdirectory( Threads )
add_subdirectory( Traits )
add_subdirectory( Tuple )
add_subdirectory( TypeDeduction )
add_subdirectory( move_examples )
add_subdirectory( TypesAndValues )
add_subdirectory( Alignment )
