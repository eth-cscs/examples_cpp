file( GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )

message(${CMAKE_CXX_FLAGS})
foreach( target_s ${SOURCES} )
    string( REPLACE ".cpp" "" target_n ${target_s} )
    add_executable( ${target_n} ${target_s} )
endforeach()

add_subdirectory(BrokenABI)
