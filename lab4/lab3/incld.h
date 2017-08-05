#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <door.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#define DOORNAME "./door"
#define SEM_NAME "./sem"
#define MAX_LINE 256    //длина строки 
#define MAX_ARGS 80    //длина строки 
#define IPC_FILE "./ipc_file"
struct plnm 
{
	double* ptr;
	unsigned int size;
};
int SplitString(char *s,const char* delim,int* argsc,char** args);
void* server();
void* client();
typedef struct plnm polynom;
