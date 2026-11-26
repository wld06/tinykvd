CC     = gcc
CFLAGS = -std=gnu17 -Wall -Wextra -g -fsanitize=address,undefined

# Common code used by server and client
COMMON = src/common/*.c

# Compile the server and run it
server:
	$(CC) $(CFLAGS) -o tinykvd src/server/*.c $(COMMON)
	./tinykvd

# Compile the client and run it
client:
	$(CC) $(CFLAGS) -o tinykv-cli src/client/*.c $(COMMON)
	./tinykv-cli

# Remove the exec
clean:
	rm -f tinykvd tinykv-cli

# Command names
.PHONY: server client clean
