#include "incld.h"
double* multiply(polynom*p1,polynom* p2)
{
	int n=p1->size-1;
	int m=p2->size-1;
	double* ptr=calloc(n*m+1,sizeof(double));
	for (register int i=0;i<n;++i)
	{
		for(register int j=0;j<m;++j)
		{
			ptr[i+j]+=p1->ptr[i]*p2->ptr[j];
		}
	}
	return ptr;
}
void server_proc(void *cookie, char *argp, size_t arg_size, door_desc_t *dp, uint_t n_desc)
{
	FILE* fs;
	int fd;
	char buf[MAX_LINE];
	char* args[MAX_ARGS];
	int argsc;
	door_arg_t arg;
	polynom p1,p2, pr;
	fs=fopen(argp,"r");
		/*//1
	
		*/
	char* args[MAX_ARGS];
	int argsc;
	fgets(buf,MAX_LINE,fs);
	StringSplit(buf," ",&argsc,args);
	p1.ptr=calloc(argsc,sizeof(double));
	for (int i=0;i<argsc;++i)
	{
		p1.ptr[i]=atof(args[i]);
	}
	p1.size=argsc;
	fgets(buf,MAX_LINE,fs);
	StringSplit(buf," ",&argsc,args);
	p2.ptr=calloc(argsc,sizeof(double));
	for (int i=0;i<argsc;++i)
	{
		p2.ptr[i]=atof(args[i]);
	}
	p2.size=argsc;
	fclose(fs);
	unlink(argp);
	pr.ptr=multiply(&p1,&p2);
	pr.size=p1.size*p2.size+1;
	fd=open(argp,O_CREAT|O_WRONLY);
	for (register int i=0;i<pr.size;++i)
	{
		write(fd,(char*)(&(pr.ptr[i])),sizeof(double));	
	}
	argsc=pr.size;
	close(fd);
	door_return((char*)(&argsc), sizeof(argsc),NULL,0);
}
void* server()
{
	int dd;
	sem_t* s=sem_open(SEM_NAME,0);
	dd = door_create(server_proc, NULL, 0 );
	unlink(DOORNAME);
	close( open(DOORNAME, O_CREAT|O_RDWR, 0660 ));
	fattach( dd, DOORNAME );
    sem_wait(s);   
}

