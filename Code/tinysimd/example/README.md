## Example code for asm generation

Source `*.cc` in this directory will be compiled to assembly and filtered
for readability, to produce corresponding files `*.asm` in the build directory.

`make examples` will compile all examples; `make ex_foo.asm` will produce
just `ex_foo.asm`.
