CC=gcc
LIBS=-ldoor
FLAGS=#-std=c99
TARGET=server
$(TARGET): server.o main.o
	$(CC) $(FLAGS) -o $(@) server.o main.o $(LIBS)
main.o: main.c
	$(CC) $(FLAGS) -o $(@) -c main.c  $(LIBS)
server.o: server.c
	$(CC) $(FLAGS) -o $(@) -c server.c  $(LIBS)
clean:
	rm -f *.o
	echo "All .o files are removed"
all: server.c main.c
	$(CC) $(FLAGS) -o $(TARGET) server.c main.c $(LIBS)
