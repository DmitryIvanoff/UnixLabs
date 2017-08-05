#include "incld.h"
double* multiplyPol(polynom*p1,polynom* p2)
{
	int n=p1->size-1;
	int m=p2->size-1;
	double* ptr=calloc(n*m+1,sizeof(double));
	register int i;
	register int j;
	for (i=0;i<n;++i)
	{
		for(j=0;j<m;++j)
		{
			ptr[i+j]+=p1->ptr[i]*p2->ptr[j];
		}
	}
	return ptr;
}
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
polynom p1,p2,pr;
bool entry=FALSE;
void server_proc(void *cookie, char *argp, size_t arg_size, door_desc_t *dp, uint_t n_desc)
{
	door_arg_t arg;
	if (!entry)                    //если передаем первый полином 
	{							  //записываем его в p1
	  if (!pr.ptr)
	  {
		free(pr,ptr);
	  }
	  p1.ptr=malloc(arg_size);
	  p1.size=arg_size/sizeof(double);
	  double* ptr;
	  ptr=(double*)argp;
	  register int i;
	  for (i=0;i<p1.size;++i)
	  {
		 p1.ptr[i]=ptr[i];	
	  }
	  entry=TRUE;
	  door_return(NULL, 0,NULL,0); //возврат из двери
	}
	else							//если передаем второй полином
	{
		p2.ptr=malloc(arg_size);
	    p2.size=arg_size/sizeof(double);
	    double* ptr;
	    ptr=(double*)argp;
		register int i;
	    for (i=0;i<p2.size;++i)
	    {
	  	 p2.ptr[i]=ptr[i];	
	    }
		pr.ptr=multiplyPol(&p1,&p2);//формируем результирующий полином
	    pr.size=p1.size*p2.size+1;
		free(p1.ptr);
		free(p2.ptr);
		entry=FALSE;
	    door_return((char*)(pr.ptr), pr.size*sizeof(double),NULL,0);
	}	
}


