CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -Iinclude

SOURCES = main.c server.c state.c

healthd: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o healthd
