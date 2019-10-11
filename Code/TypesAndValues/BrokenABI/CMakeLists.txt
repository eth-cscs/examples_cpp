add_library(my_f SHARED library.cpp library.hpp pair1.hpp pair2.hpp)

add_executable(broken broken.cpp library.hpp pair1.hpp pair2.hpp)
target_link_libraries(broken my_f)
