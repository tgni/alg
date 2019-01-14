.PHONY: tool clean

ARFLAGS := r
AR := ar
CC := gcc
RUNLIB := ranlib
TOOLLIB := libtool.a

$(TOOLLIB): tool.o
	$(AR) $(ARFLAGS) $@ $^
	$(RUNLIB) $@

clean:
	rm *.a *.o -f
