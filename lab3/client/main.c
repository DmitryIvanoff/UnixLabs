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
        //разбор значений,дин созд масс, иниц polynom p1,p2
		printf("Введите первый полином. Вводите коэффициенты, начиная\
	    со свободного члена");
		char* args[MAX_ARGS];
		char buf[MAX_LINE];
		int argsc;
		fgets(buf,MAX_LINE,stdin);
		printf("%s",buf);
		SplitString(buf," ",&argsc,args);
		p1->ptr=calloc(argsc,sizeof(double));
		for (int i=0;i<argsc;++i)
		{
			p1->ptr[i]=atof(args[i]);
		}
		printf("Введите второй полином.");
		fgets(buf,MAX_LINE,stdin);
	    printf("%s",buf);
		SplitString(buf," ",&argsc,args);
		p2->ptr=calloc(argsc,sizeof(double));
		for (int i=0;i<argsc;++i)
		{
			p2->ptr[i]=atof(args[i]);
		}
}

int main(int argc,const char** argv)
{
	int fd;
	door_arg_t arg;
	polynom p1,p2,oval;
	//чтение полиномов с клаиатуры и запись в p1,p2
    ReadFromKBD(&p1,&p2);
	//открытие двери
    fd = open(DOORNAME, O_RDWR); 
		arg.data_ptr = (char*)(p1.ptr);
		arg.data_size = sizeof(double)*p1.size;
		arg.desc_ptr = NULL;
		arg.desc_num = 0;
		arg.rbuf = NULL;
		arg.rsize = 0;
		door_call( fd, &arg );//передаем первый полином, ничего не возвращаем
		arg.data_ptr = (char*)(p2.ptr);
		arg.data_size = sizeof(double)*p2.size;
		arg.desc_ptr = NULL;
		arg.desc_num = 0;
		arg.rbuf = (char*)(oval.ptr);
		arg.rsize = sizeof(double);
		door_call( fd, &arg );//передаем второй полином,возвращаем результат
	double d;
	//выводим полином на экран
	for (int i=0;i<oval.size;++i)
	{
	    //read(fd,(char*)&d,sizeof(d));
		d=oval.ptr[i];
		printf("%f*x^%d+",d,i);
	}
	free(p1.ptr);
	free(p2.ptr);
	close(fd);
}


