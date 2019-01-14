
CFLAGS  := -I../include -I../lib
LDFLAGS := -L../lib
#OBJS    := 2.1-4.c
OBJS    := 2.2-2.c
TOOLLIB := ../lib/libtool.a
TARGET  := test

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(TOOLLIB)
	gcc $(CFLAGS) $< -o $@ $(TOOLLIB)

$(TOOLLIB):
	cd ../lib; make

clean:
	rm *.o -f
	cd ../lib; make clean
