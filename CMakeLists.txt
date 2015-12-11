cmake_minimum_required( VERSION 3.0.0 )
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project( CPPEXAMPLES )
enable_language( CXX )

set (ADDITIONAL_CXX_FLAGS "-std=c++14")
set(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH} "${CMAKE_BINARY_DIR}/build")

list(APPEND SRCFILES ./Code/Solution/main_storage.cpp ./Code/Solution/main_tuple.cpp ./Code/Traits/traits.cpp ./Code/Traits/traits1.cpp ./Code/Partial_Specialization/partial.cpp ./Code/Partial_Specialization/partial_protected.cpp ./Code/Partial_Specialization/shape.cpp)



foreach(srcfile IN LISTS SRCFILES )
    message("srcfile ${srcfile}")
    GET_FILENAME_COMPONENT(target_name ${srcfile} NAME_WE)
    message("target ${target_name}")
    add_executable(${target_name}   ${srcfile})
    set_target_properties(${target_name} PROPERTIES COMPILE_FLAGS ${ADDITIONAL_CXX_FLAGS})
endforeach()
