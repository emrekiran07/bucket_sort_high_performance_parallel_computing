CC=gcc
CFLAGS= -g -O3
DEPS =
OBJ = bucketsort_serial.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LIB)

bucketsort_serial: $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o bucketsort_serial	
