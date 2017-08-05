#include <sys/types.h>
#include <getopt.h>
#include <sys/errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAX_LINE 80 
#define MAX_ARGS 20 
#define TRUE 1;
#define FALSE 0;

int ReadArgString(char *s,size_t size) 
{
    int err=0;
    gets(s);
    /*if(fgets(s, size, stdin)==NULL)

        err=-1;

        return err;

    };
*/
    if (!(strcmp(s,"")))
    {
		err=-1;
	};
	return err;
}

int SplitString(char *s,const char* delim,int* argsc,char** args) 
{
        unsigned short count=0;
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

int main(int argc,const char** argv)
{
	int q=TRUE;     
    int error=0;	
    while(q)
	{   
        char * args[MAX_ARGS];
	    int c;
		char* a[2];
        int argsc=0;
        int rez=0;
        char str[MAX_LINE]; 
		int eflag=FALSE;
		FILE* f;
	    int opflag=0;   //1-IPC_NOWAIT,2-SEM_UNDO
		//char opflag[MAX_LINE];
		//char sargs[MAX_LINE];
		//char opargs[MAX_LINE];
		//read from stdin
        if (ReadArgString(str,sizeof(str))!=0)
		{
			printf("%s","Error! Usage: <pathname> [-c|-e|-o [-n|-u]|-s|-g|-q] [args]");
			continue;
		};
		//разбиваем строку на массив строк
	    if (SplitString(str," ",&argsc,args)!=0)
		{
			printf("%s","Error! Usage: <pathname> [-c|-e|-o [-n|-u]|-s|-g|-q] [args]");    
			continue;
		};
        /* 
		printf("%d %c",argsc,'\n');
        for (register int i=0;i<argsc;++i)
        {
		printf("%s %c",args[i],'');
		}
		*/
        while ((rez = getopt(argsc,args,"c:i:es:ungo:mqr")) != -1)
        {
		   switch (rez)
		   {	
            case 'e': 
			    eflag=TRUE;
				break;		   
		    case 'c':
				c=semcreate(args[0],atoi(optarg),eflag);
      	        //printf("Error: %d",c); 
                goto cont;				
				break;
		    case 's':
				strcpy(str,optarg);
				if (SplitString(str,",",&c,a)!=0)
				{
			     printf("Error!Не удалось разобрать строку. Usage: -s [sem_num,sem_val]\n");
		         continue;
				};
				//printf("found argument \"s=%s\".\n",optarg);  
				/*for (register int i=0;i<c;++i)
				{
					printf("%s %c",a[i],' ');
				}*/
			    c=semsetvalue(args[0],atoi(a[0]),atoi(a[1]));
				//printf("Error: %d \n",c); 
				//goto cont;
				break;
		    case 'n': 
			    opflag=1;
				break;	
		    case 'u': 
			    opflag=2;
				break;	
		    case 'o': 
			    semops(args[0],optarg,opflag);
				//goto cont;
				break;
		    case 'i': 
			    //printf("found argument \"i=%s\".\n",optarg); 
			    c=semsetvalues(args[0],optarg); 
				//printf("Error: %d \n",c); 
				//goto cont;
			    break;
		    case 'r': 
			    c=semrm(args[0]); 
				//printf("Error: %d \n",c); 
				//goto cont;
			    break;
		    case 'g': 
			    c=semgetvalues(args[0]);
				//printf("Error: %d \n",c); 
				//goto cont;
				break;
		    case 'm': 
				if((f=fopen("./man","r"))==NULL)
				{
					printf("Error!Такого файла нет!\n");
				//	goto cont;
					//continue;
				};
				while(fgets(str,sizeof(str),f)!=NULL)
				{
					printf("%s \n",str);
				} 
				fclose(f);
				//goto cont;
		        break;
            case 'q': 
			    printf("Спасибо за пользование!\n");
				q=0;
                break;
            case '?': 
			    printf("Error found!\n");
				goto cont;
			    break;
               
            };
			
	    };
        cont:
		optarg=NULL;
		eflag=FALSE;
        optind=0;
	}	
	exit(0);
}
