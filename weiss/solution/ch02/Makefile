#gcc compiler template
.PHONY: all gene_rand

OBJECTS = random_permutation.o

CFLAGS = -g -Werror -Wall -O0
LOCFLAGS = -I ../inc
all: max_sum

gene_rand: $(OBJECTS)
	$(CC) $(CFLAGS) $(LOCFLAGS) $< -o $@

max_sum: max_sum.o
	$(CC) $(CFLAGS) $(LOCFLAGS) $< -o $@

clean:
	rm -rf *.o gene_rand
