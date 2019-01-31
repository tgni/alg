dirs := binheap crc eightqueen fib fsm graph greedy hash hweight kmp list math prio_hash scheduler slice sort sudoku timer tree
all:
	$(foreach N,$(dirs),make -C $(N) &&) :

clean:
	$(foreach N,$(dirs),make -C $(N) clean &&) :

