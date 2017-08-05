#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <door.h>
#include <fcntl.h>
#define DOORNAME "./door"
#define MAX_LINE 256    //длина строки 
#define MAX_ARGS 80    //длина строки 
struct plnm 
{
	double* ptr;
	unsigned int size;
};
typedef struct plnm polynom;
