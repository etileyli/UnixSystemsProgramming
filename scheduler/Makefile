all: output

run: scheduler
	./scheduler

output: scheduler.o ds.o
	gcc -pthread -lrt scheduler.o ds.o -o scheduler

scheduler.o: scheduler.c
	gcc -c scheduler.c

ds.o: ds.c ds.h
	gcc -c ds.c

clean:
	rm *.o scheduler
