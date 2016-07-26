CFLAGS = -g -Wall 
CC = gcc

objects = main.o class_stats.o

test: $(objects)
	$(CC) -o stats $(objects)

main.o: main.c class_stats.h
class_stats.o: class_stats.c class_stats.h

.PHONY : clean
clean: 
	rm stats $(objects)
