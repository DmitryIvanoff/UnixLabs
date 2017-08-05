CC=gcc
LIBS=-ldoor -I./
FLAGS=#-std=c99
TARGET=lab3
$(TARGET): server.o client.o main.o
	$(CC) $(FLAGS) -o $(@) server.o client.o main.o $(LIBS)
main.o: main.c
	$(CC) $(FLAGS) -o $(@) -c main.c  $(LIBS)
server.o: server.c
	$(CC) $(FLAGS) -o $(@) -c server.c  $(LIBS)
client.o: client.c
	$(CC) $(FLAGS) -o $(@) -c client.c $(LIBS)
clean:
	rm -f *.o
	echo "All .o files are removed"
all: server.c client.c main.c
	$(CC) $(FLAGS) -o $(TARGET) server.c client.c main.c $(LIBS)
