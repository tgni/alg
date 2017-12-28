#gcc compiler template
OBJECTS = list.o PrintLots.o

CFLAGS = -I ../inc
CC = gcc
CFLAGS += -g -Wall -Werror -O0

export LOCFLAGS

test: $(OBJECTS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(OBJECTS)
