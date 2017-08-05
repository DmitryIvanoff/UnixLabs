#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define F_TYPE float   //тип вещественного числа
#define MAX_FORMAT_L 80 //длина строки формата
#define MAX_LINE 256    //длина строки 
#define e 0.00001  //точность
void EquationSolve(int w_desc,F_TYPE a, F_TYPE b, F_TYPE c)
{  
   size_t size;
   char str1[MAX_LINE];
   char str2[MAX_LINE];
   F_TYPE x1,x2;
   if(abs(a-0)<e)
    {
        if(abs(b-0)<e)
        {
            if(abs(c-0)<e)
            {
				strcpy(str1,"x-lyboe4islo");
				int len=strlen(str1);
				if (str1[len-1]=='\n')
					--len;
                write(w_desc,str1,len);
            }
            else
            {
                strcpy(str1,"x-lyboe4islo");
				int len=strlen(str1);
				if (str1[len-1]=='\n')
					--len;
                write(w_desc,str1,len);
            }
        }
        else
        {
            x1=-c/b;
            write(w_desc,&x1,sizeof(x1));
        }
    }
    else
    {
        F_TYPE d;
        d = b * b - 4 * a * c;
        if(d < 0)
        {
            strcpy(str1,"kornei net");
            int len=strlen(str1);
				if (str1[len-1]=='\n')
					--len;
                write(w_desc,str1,len);
        }
        else
        {
            if(d == 0)
            {
                x1=-b/(2*a);
                write(w_desc,&x1,sizeof(x1));
            }
            else
            {
                x1=(-b+sqrt(d))/(2*a);
                x2=(-b-sqrt(d))/(2*a); 
                //printf("%f %f %c",x1,x2,'\n');
                strcpy(str1,"x1= ");
                strcpy(str2,"x2= ");
				int len=strlen(str1);
				if (str1[len-1]=='\n')
					--len;
                write(w_desc,str1,len);
                write(w_desc,&x1,sizeof(x1));
				len=strlen(str2);
				if (str2[len-1]=='\n')
					--len;
                write(w_desc,str2,len);
                write(w_desc,&x2,sizeof(x2));
            }
        }
        
    }

	
}



int main(int argc,const char** argv)
{
  int pipe1[2];   //для передачи данных (родитель-потомок)
  int pipe2[2];   //для передачи данных (потомок-родитель)   
  pipe(pipe1);
  pipe(pipe2);
  pid_t childpid;
  
  childpid=fork(); 
  if ((childpid)==0)
  {
       // закрываем все, что связано с родительским процессом
        close(pipe1[1]);
        close(pipe2[0]);
	char coef[80];
	F_TYPE coeffs[3];
	for(register int i=0;i<3;++i)
	{
           read(pipe1[0],coef,nBytes[i]);
	   coeffs[i]=atof(coef);
	}
        EquationSolve(pipe2[1],coeffs[0], coeffs[1], coeffs[2]);
        exit(0);
  }
  else
   {  
      if (childpid==-1)
      {
         printf("error");    
         exit(-1);
      }
   }
  //waitpid(childpid,NULL,0);
// закрываем все, что связано с дочерним процессом
  close(pipe1[0]);
  close(pipe2[1]);
  size_t nBytes[3];
  if (argc==4)
  {
    for(register int i=1;i<4;++i)
	{
	   nBytes[i-1]=sizeof(argv[i]);
       write(pipe1[1],argv[i],nBytes[i-1]);
	}
    
  }
  else
  {
	  printf("%s","Error: format is: [program] a b c");
	  exit(-1);
  }
  char str[MAX_LINE]; //для считывания строки
 ///* 
  int n;
  while ((n=read(pipe2[0],str,MAX_LINE))>0)
  {
	  write(STDOUT_FILENO,str,n);
  }
  waitpid(childpid,NULL,0);
 //*/
  exit(0);
  
}
