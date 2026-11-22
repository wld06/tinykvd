CC      = gcc
CFLAGS  = -std=gnu17 -Wall -Wextra -g -fsanitize=address,undefined
COMMON  = src/common/*.c

all: tinykvd tinykv-cli

tinykvd: src/server/*.c $(COMMON)
	$(CC) $(CFLAGS) -o $@ $^

tinykv-cli: src/client/*.c $(COMMON)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f tinykvd tinykv-cli