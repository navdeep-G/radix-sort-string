all: build

build: radix.c main.c
	gcc -Wall -Wextra -O2 -std=c99 -o radix radix.c main.c

clean:
	rm -f *.o radix
