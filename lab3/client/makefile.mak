CC=gcc
LIBS=-ldoor 
FLAGS=#-std=c99
TARGET=client.exe
$(TARGET): main.o
	$(CC) $(FLAGS) -o $(@) main.o $(LIBS)
main.o: main.c
	$(CC) $(FLAGS) -o $(@) -c main.c  $(LIBS)
clean:
	rm -f *.o
	echo "All .o files are removed"
all: main.c
	$(CC) $(FLAGS) -o $(TARGET)  main.c $(LIBS)
