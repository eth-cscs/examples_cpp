cmake_minimum_required( VERSION 3.0.0 )

project( examples_cpp )
enable_language( CXX )


# Needed only by CountDigits, which is turned off -- find_package( Boost COMPONENTS program_options REQUIRED )

include_directories( SYSTEM ${Boost_INCLUDE_DIRS} )
link_directories( ${Boost_LIBRARY_DIRS} )
set (CMAKE_CXX_FLAGS "-std=c++14")

FILE(GLOB_RECURSE COMMON_INC "*.hpp")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_DIR})

add_subdirectory( Intro )
add_subdirectory( CRTP )
#add_subdirectory( CountDigits ) # depends on boost::program_options
#add_subdirectory( Extents ) # depends on boost::program_options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "5.0")
    add_subdirectory( Constexpr )
  else()
    message("Constexpr examples not supported by your compiler")
  endif()
else()
  add_subdirectory( Constexpr )
endif()
add_subdirectory( EnumClasses )
add_subdirectory( Generic )
add_subdirectory( Lambdas )
add_subdirectory( Proxy )
add_subdirectory( SmartPtrs )
add_subdirectory( Random )
add_subdirectory( Templates )
add_subdirectory( TemplateMetaProgramming )
add_subdirectory( Threads )
add_subdirectory( Traits )
add_subdirectory( TypeDeduction )
add_subdirectory( move_examples )
add_subdirectory( STL )
add_subdirectory( TypesAndValues )
add_subdirectory( Alignment )
add_subdirectory( Exceptions )
