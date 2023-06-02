cc = gcc
CFLAGS = -g -Wall

all: st_pipeline

st_pipeline: st_pipeline.o queue.o
	$(CC) $(FLAGS) -o st_pipeline st_pipeline.o queue.o

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $^

.PHONY: all clean

clean:
	rm -f *.o *.gch st_pipeline