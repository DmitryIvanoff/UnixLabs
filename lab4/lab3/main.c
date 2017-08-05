/*#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DOORNAME ./door
#define SEM_NAME ./sem*/
#include "incld.h"


//main создает два потока(можно и процесса) \
client и server и семафор(можно и mutex)   \
дальше сервер создает дверь и ждет(с помошью семафора)\
когда клиент передаст ему данные(о данных ниже). \
далее сервер перемножает полиномы и так же отправляет данные \
клиент все выводит 

//данные, передаваемые через дверь могут быть: \
1) две структуры с коэффициентами на входе и одна на выходе \
2) открытый дескриптор файла, куда пишем посчитанные сервером коэфф \
 и считываем передаваемые клиентом \
3) имя файла, ---//----
//выбрал вариант 3
int main(int argc,const char** argv)
{
	sem_t* sem;
	sem=sem_open(SEM_NAME,O_CREAT|O_EXCL,S_IWUSR | S_IRUSR,1);
    sem_close(sem);
	pthread_t serv;
	pthread_t clnt;
	pthread_setconcurrency(2);
	pthread_create(&serv,NULL,server,NULL);
	pthread_create(&clnt,NULL,client,NULL);
	pthread_join(serv,NULL);
	pthread_join(clnt,NULL);
	sem_close(sem);
	sem_unlink(SEM_NAME);
    //создаем два именованных потока POSIX
     
	exit(0);

}