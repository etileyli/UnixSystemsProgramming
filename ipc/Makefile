#gcc -pthread -lrt -o ipc ipc.c; ./ipc

all: output

run: ipc
	./ipc

output: ipc.o
	gcc ipc.o -o ipc

ipc.o: ipc.c
	gcc - pthread -lrt -c ipc.c

clean:
	rm *.o ipc
