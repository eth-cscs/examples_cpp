.SECONDARY:

top:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))

OPTFLAGS?=-O3 -march=native
CXXFLAGS+=$(OPTFLAGS) -MMD -MP -std=c++14 -g -pthread -ffp-contract=off
CPPFLAGS+=-I $(top)include

RMDIR:=rm -d -f

.PHONY: all clean cleanall realclean
all:: examples unit benchmarks
clean::
celeanall::
realclean:: cleanall

# $(call build-cc, src-prefix, obj-prefix, source)
define build-cc
$(2)$(patsubst %.cc,%.o,$(3)): $(1)$(3) | $(dir $(2))
	$$(COMPILE.cc) $$< $$(OUTPUT_OPTION)

-include $(2)$(patsubst %.cc,%.d,$(3))
clean:: ; $$(RM) $(2)$(patsubst %.cc,%.o,$(3))
cleanall:: clean; $$(RM) $(2)$(patsubst %.cc,%.d,$(3))
endef

# $(call dump-cc-asm, src-prefix, obj-prefix, source)
define dump-cc-asm
$(2)$(patsubst %.cc,%.s,$(3)): $(1)$(3) | $(dir $(2))
	$$(filter-out -c -g,$$(COMPILE.cc)) -S $$< $$(OUTPUT_OPTION)

-include $(2)$(patsubst %.cc,%.d,$(3))
clean:: ; $$(RM) $(2)$(patsubst %.cc,%.s,$(3))
cleanall:: clean; $$(RM) $(2)$(patsubst %.cc,%.d,$(3))
endef

# $(call build-cclib, libname, src-prefix, obj-prefix, sources)
define build-cclib
$(foreach src,$(4),$(eval $(call build-cc,$(2),$(3),$(src))))
$(1): $(foreach src,$(4),$(3)$(patsubst %.cc,%.o,$(src)))
	$$(AR) $$(ARFLAGS) $$@ $$^

cleanall:: clean; $(RM) $(1)
endef

# $(call build-ccexe, libname, src-prefix, obj-prefix, sources)
define build-ccexe
$(foreach src,$(4),$(eval $(call build-cc,$(2),$(3),$(src))))
$(1): $(foreach src,$(4),$(3)$(patsubst %.cc,%.o,$(src)))
	$$(LINK.cc) $$^ $$(OUTPUT_OPTION) $$(LOADLIBES) $$(LDLIBS)

cleanall:: ; $(RM) $(1)
endef

### Google Test

gtest-top:=$(top)import/gtest/googletest

_gtest/: ; mkdir -p $@
realclean:: cleanall; $(RMDIR) _gtest

libgtest.a: CPPFLAGS+=-I $(gtest-top) -I $(gtest-top)/include
$(eval $(call build-cclib,libgtest.a,$(gtest-top)/src/,_gtest/,gtest-all.cc))

### Google Benchmark

gbench-top:=$(top)import/gbench
gbench-srcdir:=$(gbench-top)/src
gbench-src:=$(notdir $(wildcard $(gbench-srcdir)/*.cc))

_gbench/: ; mkdir -p $@
realclean:: cleanall; $(RMDIR) _gbench

libgbench.a: CPPFLAGS+=-I $(gbench-top)/include -DNDEBUG
$(eval $(call build-cclib,libgbench.a,$(gbench-srcdir)/,_gbench/,$(gbench-src)))

### Unit tests

test-srcdir:=$(top)test
test-src:=$(notdir $(wildcard $(test-srcdir)/*.cc))

_unit/: ; mkdir -p $@
realclean:: cleanall; $(RMDIR) _unit

unit: CPPFLAGS+=-I $(gtest-top)/include -I $(top)/include -DNDEBUG
unit: LDLIBS+=libgtest.a
unit: libgtest.a
$(eval $(call build-ccexe,unit,$(test-srcdir)/,_unit/,$(test-src)))

### Benchmarks

bench-srcdir:=$(top)bench
bench-src:=$(notdir $(wildcard $(bench-srcdir)/*.cc))

_bench/: ; mkdir -p $@
realclean:: cleanall; $(RMDIR) _bench

.PHONY: benchmarks
define build-bench
benchmarks:: $(1)
$(1): CPPFLAGS+=-I $(gbench-top)/include -I $(top)/include
$(1): LDLIBS+=libgbench.a
$(1): libgbench.a
$(eval $(call build-ccexe,$(1),$(bench-srcdir)/,_bench/,$(1).cc))
endef

$(foreach src,$(notdir $(wildcard $(bench-srcdir)/*.cc)),\
$(eval $(call build-bench,$(basename $(src)))))

### Asm examples

example-srcdir:=$(top)example
example-src:=$(notdir $(wildcard $(example-srcdir)/*.cc))

_asmex/: ; mkdir -p $@
realclean:: cleanall; $(RMDIR) _asmex

.PHONY: examples
define build-asm-example
$(1).s: CPPFLAGS+=-I $(top)/include
$(call dump-cc-asm,$(example-srcdir)/,_asmex/,$(1).cc)
examples:: $(1).asm
$(1).asm: _asmex/$(1).s; c++filt < $$< | grep -v '\.[a-z]\+' > $$@
cleanall:: ; $(RM) $(1).asm
endef

$(foreach src,$(notdir $(wildcard $(example-srcdir)/*.cc)),\
$(eval $(call build-asm-example,$(basename $(src)))))

