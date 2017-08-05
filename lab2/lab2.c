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
void EquationSolve(int w_desc,int f_desc,F_TYPE a, F_TYPE b, F_TYPE c)
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
                write(f_desc,"%s",2);
                write(w_desc,str1,MAX_LINE);
            }
            else
            {
                strcpy(str1,"x-lyboe4islo");
                write(f_desc,"%s",2);
                write(w_desc,str1,MAX_LINE); 
            }
        }
        else
        {
            x1=-c/b;
            write(f_desc,"%f",2);
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
            write(f_desc,"%s",2);
            write(w_desc,str1,MAX_LINE);
        }
        else
        {
            if(d == 0)
            {
                x1=-b/(2*a);
                write(f_desc,"%f",2);
                write(w_desc,&x1,sizeof(x1));
            }
            else
            {
                x1=(-b+sqrt(d))/(2*a);
                x2=(-b-sqrt(d))/(2*a); 
                //printf("%f %f %c",x1,x2,'\n');
                strcpy(str1,"x1= ");
                strcpy(str2,"x2= ");
                write(f_desc,"%s%f%s%f",MAX_FORMAT_L);
                write(w_desc,str1,MAX_LINE);
                write(w_desc,&x1,sizeof(x1));
                write(w_desc,str2,MAX_LINE);
                write(w_desc,&x2,sizeof(x2));
            }
        }
        
    }

	
}



int main(int argc,const char** argv)
{
size_t s2;
  int pipe1[2];   //для передачи данных (родитель-потомок)
  int pipe2[2];   //для передачи данных (потомок-родитель)
  int pipe3[2];   //для передачи формата данных (потомок-родитель)
  pipe(pipe1);
  pipe(pipe2);
  pipe(pipe3);
  pid_t childpid;
  size_t nBytes[3];
  if (argc==4)
  {
    for(register int i=1;i<4;++i)
	{
	   nBytes[i-1]=sizeof(argv[i]);
           write(pipe1[1],argv[i],nBytes[i-1]);
	}
    
  }
  childpid=fork(); 
  if ((childpid)==0)
  {
       // закрываем все, что связано с родительским процессом
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[0]);
	char coef[80];
	F_TYPE coeffs[3];
	for(register int i=0;i<3;++i)
	{
           read(pipe1[0],coef,nBytes[i]);
	   coeffs[i]=atof(coef);
	}
	EquationSolve(pipe2[1],pipe3[1],coeffs[0], coeffs[1], coeffs[2]);
        exit(0);
  }
  else
   {  
      if (childpid==-1)
      {
         printf("error");    
         exit(0);
      }
   }
  waitpid(childpid,NULL,0);
// закрываем все, что связано с дочерним процессом
   close(pipe1[0]);
  close(pipe3[1]);
  close(pipe2[1]);
  char str[MAX_LINE]; //для считывания строки
 ///* 
  char format[MAX_FORMAT_L];//для считывания формата
  F_TYPE x;//для считывания вещественного числа
  size_t s=read(pipe3[0],format,MAX_FORMAT_L);//считываем формат
  //printf("%d",s);
  //printf("%s %c",format,'\n');
  for (register char* p=format;*p;++p)
  {
      switch(*p)
       {
         case 'f':
             s2=read(pipe2[0],&x,sizeof(F_TYPE)); 
             printf("%f %c",x,'\n');
             //printf("%d",s2);
             break;
         case 's':
              s2=read(pipe2[0],str,MAX_LINE);
              printf("%s %c",str,'\n');
              //printf("%d %c",s2,'\n');
             break;
       }
  }
  //*/

  //close(pipe1[0]);
  //close(pipe3[1]);
  //close(pipe2[1]);
  //waitpid(childpid,NULL,0);
  /*
  ssize_t n;
  while ((n=read(pipe2[0],str,MAX_LINE))>0)
  {
	  write(STDOUT_FILENO,str,MAX_LINE);
  }
  //*/
  exit(0);
  
}
