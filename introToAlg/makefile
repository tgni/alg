dirs := dp greedy start
all:
	$(foreach N,$(dirs),make -C $(N) &&) :

clean:
	$(foreach N,$(dirs),make -C $(N) clean &&) :

distclean:
	$(foreach N,$(dirs),make -C $(N) distclean &&) :

