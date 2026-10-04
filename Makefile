CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g
CPPFLAGS = -Iinclude

HEALTHD_SOURCES = main.c server.c state.c
CLIENT_SOURCES = test/test_client.c

all: healthd test_client

healthd: $(HEALTHD_SOURCES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(HEALTHD_SOURCES) -o healthd

test_client: $(CLIENT_SOURCES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CLIENT_SOURCES) -o test_client

clean:
	rm -f healthd test_client

