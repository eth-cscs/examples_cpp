g++ -c performance_fun.cxx -I./ -DSKIP_ERR -O3
g++ -c performance_13.cxx -I./ -O3
g++ -o performance_13 performance_13.o performance_fun.o -DSKIP_ERR -O3

