CC=gcc -std=c99
TARGET=lab4
$(TARGET): sem.o main.o
	$(CC) -o $(@) sem.o main.o
main.o: main.c
	$(CC) -c -o $(@) main.c
sem.o: sem.c
	$(CC) -c -o $(@) sem.c 		
clean:
	rm -f *.o
	echo "All .o files are removed"
all: server.c client.c main.c
	$(CC) -o $(TARGET) server.c client.c main.c
