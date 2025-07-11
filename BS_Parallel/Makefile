CC=gcc
CFLAGS= -g -O3
DEPS =
OBJ = bucketsort_parallel.o
LIB = -fopenmp

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LIB)

bucketsort_parallel: $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o bucketsort_parallel
