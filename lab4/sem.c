#include <sys/types.h>
#include <sys/errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 80 
#define MAX_ARGS 20 
#define SEM_A		0200	/* alter permission */
#define SEM_R		0400	/* read permission */
union semun
{
       int val;       //только для SETVAL
       struct semid_ds * buf; //только IPC_SET и IPC_STAT
       unsigned short* array;      //GETALL и SETALL
	   struct seminfo *__buf; // only in GNU/Linux
};
int semcreate(const char* semkey,int nsems,int eflag)
{
	/*char str[MAX_LINE];
    strcpy(str,"touch ");
    strcat(str,semkey);
    system(str);*/
	printf("----------\n");
    int semid, oflag;
	unsigned short n;
	struct semid_ds seminfo;
	union semun arg;
     oflag=IPC_CREAT|SEM_A|SEM_R ;
	if (eflag)
	{
	  oflag|=IPC_EXCL;	
	}
       // printf("%d %c",nsems,'\n');
	if ((semid=semget(ftok(semkey,0),nsems,oflag))>=0)
	{
        //printf("%s%d%s%d%c","key: ",ftok(semkey,0),"semid:",semid,'\n');
		arg.buf=&seminfo;//вся информация хранится в semid_ds seminfo
		semctl(semid,0,IPC_STAT,arg);
		n=arg.buf->sem_nsems;
		printf("Набор семафоров id: %d создан.\nКол-во cемафоров в наборе \
		%d\nСемафор нужно проиницилизировать с помощью команды -i [value1,..,valueNsem]\n",semid,n);
	}
	else
	{
		if (errno==EEXIST)
		{
			if((semid=semget(ftok(semkey,0),0,0))>=0)
	
			{
				//printf("%d",semid);
				arg.buf=&seminfo;//вся информация хранится в semid_ds seminfo
				semctl(semid,0,IPC_STAT,arg);
				n=arg.buf->sem_nsems;
				printf("Семафор уже существует id: %d.Кол-во семафоров: %d\n",semid,n);
			};
		}
		else
		{
			printf("----------\n");
			return errno; 
		}
	}
	printf("----------\n");
	return 0;
}
int semops(const char* semkey,const char* sem_op, int opflag)
{
	/*
	struct sembuf 
	{
		short sem_num;       //номер семафора 0..nsems-1
		short sem_op;        //операция с семафором <0 0 >0
		short sem_flg;       //флаги операции
	}
	*/
	printf("----------\n");
	int semid, flag, nops,error;
	char * args[MAX_ARGS];
	struct sembuf* ptr; 
	char s[MAX_LINE];
	strcpy(s,sem_op);
	if (SplitString(s,",",&nops,args)!=0)
		{
			printf("Error!Не удалось разобрать строку\n");
			printf("----------\n");
		    return -1;
		};
	switch (opflag)
	{
		case 1:
			flag=IPC_NOWAIT;
			break;
	    case 2:
			flag=SEM_UNDO;
		    break;
	    default: 
		    flag=0;
		    break;
	}
	//Открываем существующий семафор
	if((semid=semget(ftok(semkey,0),0,0))<0)
	{
		printf("%s","Error! Не удалось открыть\n");
		printf("----------\n");
		return semid;
	};
	//создаем массив операций (структур sembuf)
	ptr=calloc(nops,sizeof(struct sembuf));
	for (int i=0;i<nops;++i)
	{
		ptr[i].sem_num=i;
		ptr[i].sem_op=atoi(args[i]);
		ptr[i].sem_flg=flag;
	}
    if((error=semop(semid,ptr,nops))<0)
	{
		printf("Error!Операция не завершена");
		printf("----------\n");
		 return error;
	}
	printf("Все в порядке!");
	printf("----------\n");
	return 0;
}
int semrm(const char* semkey)
{
	printf("----------\n");
	int semid,error;
	if((semid=semget(ftok(semkey,0),0,0))<0)
	{
		printf("%s","Error! Не удалось открыть\n");
		printf("----------\n");
		return semid;
	};
	error=semctl(semid,0,IPC_RMID);
	if (error>=0)
	{
		printf("%s with id %d was deleted\n",semkey,semid);
	}
	printf("----------\n");
	return error;
}
int semsetvalues(const char* semkey,const char* semval)
{
	/*
	union semun 
	{
		int val;       //только для SETVAL
		struct semid_ds * buf; //только IPC_SET и IPC_STAT
		unsigned short* array;      //GETALL и SETALL
	}
	*/
	printf("----------\n");
    int semid,argsc,error;
	unsigned short nsems;
	unsigned short* ptr;
	char * args[MAX_ARGS];
	char s[MAX_LINE];
	strcpy(s,semval);
	union semun arg;
    struct semid_ds seminfo;
	if (SplitString(s,",",&argsc,args)!=0)
		{
			printf("Error!Не удалось разобрать строку\n");
			printf("----------\n");
		    return -1;
		};
    //откроем существующий семафор
    if((semid=semget(ftok(semkey,0),0,0))<0)
	{
		printf("Error!Не существует такого семафора\n");
		printf("----------\n");
	    return -1;
	};
	arg.buf=&seminfo;//вся информация хранится в semid_ds seminfo
	//узнаем сколько семафоров в наборе
	error=semctl(semid,0,IPC_STAT,arg);
	if (error<0)
	{
		printf("----------\n");
		return error;
	}
	nsems=arg.buf->sem_nsems;
    printf("Число семафоров в наборе (%d)\n",nsems);
	if (argsc!=nsems)
	{
		printf("Error!Число аргументов и семафоров в наборе отличается (%d)\n",nsems);
		printf("----------\n");
		return -1;
	}
	//зададим массив значений 
	ptr=calloc(nsems,sizeof(unsigned short));
	arg.array=ptr;
	for (int i=0;i<nsems;++i)
	{
		ptr[i]=atoi(args[i]);
		//printf("%d",ptr[i]);
	}
	//
	error=semctl(semid,0,SETALL,arg);
	if(error<0)
	{
		printf("Error!Не смогли установить значения\n");
		printf("----------\n");
	    return -1;
	}
	printf("Проинициализировали набор семафоров id:%d!\n",semid);
	printf("----------\n");
	return 0;
}
int semsetvalue(const char* semkey,int sem_num,int semval)
{
	/*
	union semun 
	{
		int val;       //только для SETVAL
		struct semid_ds * buf; //только IPC_SET и IPC_STAT
		unsigned short* array;      //GETALL и SETALL
	}
	*/
	printf("----------\n");
	int err=0;
    int semid;
	union semun arg;
   // struct semid_ds seminfo;
    if ((semid=semget(ftok(semkey,0),0,0))<0)
	{
	    printf("Error!Не существует такого семафора\n");
		printf("----------\n");
	    return semid;
	}
	//arg.buf=&seminfo;//вся информация хранится в semid_ds seminfo
	//узнаем сколько семафоров в наборе
	//semctl(semid,0,IPC_STAT,arg);
	arg.val=semval;
	if ((err=semctl(semid,sem_num-1,SETVAL,arg))>=0)
	{
	    printf("Установили в наборе семафоров id: %d %d-ому семафору значение: %d\n",semid,sem_num,semval);
	}
	else
	{
		printf("Error!Не удалось установить значение\n");
		printf("----------\n");
		return err;
	}
	printf("----------\n");
	return 0;
}
int semgetvalues(const char* semkey)
{
	/*
	struct semid_ds 
	{
		struct ipc_perm sem_perm;       //разрешения на операции
		struct sem* sem_base;          //указатель на массив семафоров в наборе
		ushort sem_nsems;            //кол-во семафоров в наборе
		time_t sem_otime;             //ыер
		time_t sem_ctime;
	}
	*/
	printf("----------\n");
	int semid,nsems,error;
	error=0;
	unsigned short* ptr;
	union semun arg;
    struct semid_ds seminfo;
    //
    if((semid=semget(ftok(semkey,0),0,0))<0)
	{
		printf("Error!Не существует такого семафора\n");
		printf("----------\n");
	    return -1;
    };
	arg.buf=&seminfo;
	//
	error=semctl(semid,0,IPC_STAT,arg);
	if(error<0)
	{
		printf("Error!Не смогли получить информацию\n");
		printf("----------\n");
	    return error;
	}
	nsems=arg.buf->sem_nsems;
	
	ptr=calloc(nsems,sizeof(unsigned short));
	arg.array=ptr;
	//
	error=semctl(semid,0,GETALL,arg);
	if(error<0)
	{
		printf("Error!Не смогли получить значения\n");
		printf("----------\n");
	    return error;
	}
	for (int i=0;i<nsems;++i)
	{
		printf("semval[%d]=%d\n",i,ptr[i]);
	}
	printf("----------\n");
	return 0;
}