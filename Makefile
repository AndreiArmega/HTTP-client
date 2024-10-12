CC=gcc
CFLAGS=-I.

client: client.c requests.c helpers.c buffer.c commands.c utils.c
	$(CC) -o client client.c commands.c requests.c helpers.c buffer.c utils.c -Wall

run: client
	./client

clean:
	rm -f *.o client
