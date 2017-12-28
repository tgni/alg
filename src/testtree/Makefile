src := $(foreach i, $(shell pwd), $(wildcard $(i)/*.c))
obj := $(patsubst %.c, %.o, $(src))
run: $(obj)
	gcc $^ -o $@
