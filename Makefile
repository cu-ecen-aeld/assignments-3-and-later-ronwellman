CFLAGS=-Wall -Wextra -Wpedantic
CC=$(CROSS_COMPILE)gcc

.PHONY: all clean

all: finder-app/writer

finder-app/writer: finder-app/writer.c

clean:
	rm -rf *.o finder-app/writer