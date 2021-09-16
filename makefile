CC	= gcc
CFLAGS	= -g
TARGET	= runsim
OBJS	= driver.o testsim.o

$ (TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

runsim.o: runsim.c
	$(CC) $(CFLAGS) -c runsim.c

testsim.o: testsim.c
	$(CC) $(CFLAGS) -c testsim.c

clean:
	rm -rf *.o
