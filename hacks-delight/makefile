dirs := basics
all:
	$(foreach N,$(dirs),make -C $(N) &&) :

clean:
	$(foreach N,$(dirs),make -C $(N) clean &&) :

