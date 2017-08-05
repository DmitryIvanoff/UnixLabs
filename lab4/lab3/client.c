#include "incld.h"
int SplitString(char *s,const char* delim,int* argsc,char** args) 

{

        ushort count=0;

        int err=0;

        char * pch = strtok (s,delim); 

        while (pch != NULL)                         

        {

		  count++;

                  //printf("%s",pch);

                  args[count-1]=pch;  

                  pch = strtok (NULL, delim);

                   

        }

        (*argsc)=count;

        return err;

}
void ReadFromKBD(polynom* p1,polynom* p2)
{
        //1разбор значений,дин созд масс, иниц polynom p1,p2
		//1
		//надо передать polynom p1,p2;
		printf("Введите первый полином. Вводите коэффициенты, начиная\
	    со свободного члена");
		char* args[MAX_ARGS];
		char buf[MAX_LINE];
		int argsc;
		fgets(buf,MAX_LINE,stdin);
		SplitString(buf," ",&argsc,args);
		p1->ptr=calloc(argsc,sizeof(double));
		for (int i=0;i<argsc;++i)
		{
			p1->ptr[i]=atof(args[i]);
		}
		printf("Введите второй полином.");
		fgets(buf,MAX_LINE,stdin);
		SplitString(buf," ",&argsc,args);
		p2->ptr=calloc(argsc,sizeof(double));
		for (int i=0;i<argsc;++i)
		{
			p2->ptr[i]=atof(args[i]);
		}
			
}

void* client()
{
	
	//чтение с клавы
	int fd;
	int n;
	char buf[MAX_LINE];
	door_arg_t arg;
	fd=open(IPC_FILE,O_CREAT|O_WRONLY);
	 printf("Введите первый полином. Вводите коэффициенты, начиная\
	со свободного члена");
    fgets(buf,MAX_LINE,stdin);
	//3запись в файл
	write(fd,buf,sizeof(buf));
    printf("Введите второй полином.");
    fgets(buf,MAX_LINE,stdin);
	write(fd,buf,sizeof(buf));
	close(fd);
	        //1 polynom p1,p2;
			//1 ReadFromKBD(&p1,&p2);
	//передача аргументов в дверь
	//3
	int dd;
	int count;
	char* ival=IPC_FILE;
	dd = open(DOORNAME, O_RDWR);
	arg.data_ptr = (char*)&ival;
	arg.data_size = sizeof(ival);
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = (char*)&count;
	arg.rsize = sizeof(count);
	door_call( fd, &arg );
		/*//1
		polynom ival[2], oval;
		ival[0]=p1;
		ival[1]=p2;
		fd = open(DOORNAME, O_RDWR); 
		arg.data_ptr = (char*)&ival;
		arg.data_size = sizeof( ival );
		arg.desc_ptr = NULL;
		arg.desc_num = 0;
		arg.rbuf = oval;
		arg.rsize = sizeof( ival );
		door_call( fd, &arg );
		*/
	sem_t* s=sem_open(SEM_NAME,0);
	sem_post(s);
		//1создание выходного массива значений
	//3чтение из файла IPC_FILE
		fd=open(IPC_FILE,O_CREAT|O_WRONLY)
	//3запись в файл
	double d;
	for (int i=0;i<count;++i)
	{
	    read(fd,(char*)&d,sizeof(d));
		printf("%f*x^%d+",d,i);
	}
	close(fd);
}


