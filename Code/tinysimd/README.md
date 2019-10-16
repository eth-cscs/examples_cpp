# Demo code for Advanced C++ for HPC course.

## Building

Make sure git submodules are initialized for google test and google bench. Then:


```
mkdir build
cd build
ln -s ../Makefile

# Make unit test executable ./unit
make unit

# Make ex_xxx.asm assembly code from example source.
make examples

# Make benchmarks ./bench_xxx from sources in bench/
make benchmarks

# Remove object files.
make clean

# Remove object files, executables, libraries. and generated dependencies.
make realclean
```
