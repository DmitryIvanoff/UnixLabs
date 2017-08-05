#include <stdio.h>
#define va_start( ap, parm )  (ap)=(char*)(&(parm)+1)
#define va_arg( ap, type )    ((type*)((char*)(ap)+=sizeof(type)))

void Arguments(const char* format,...)
{
    void* args;
    va_start(args,format);
    for(register unsigned int i=0;format[i];++i)
    {
       switch(format[i])
       {
       case 'd':;
	      double *ptr= va_arg(args,double);
	      printf("%s %p %s %d %s %f %s","pointer: ",ptr," size: ",sizeof(*ptr)," value: ",*ptr," ;\n");
		break;
       case 's':;
	      char **s;
		s= va_arg(args,char*);
	      printf("%s %p %s %d %s %s %s","pointer: ",s," size: ",sizeof(*s)," value: ",*s," ;\n");
		break;
       case 'f':;
	      float * f ;
	      f= va_arg(args,float);
	      printf("%s %p %s %d %s %f %s","pointer: ",f," size: ",sizeof(*f)," value: ",*f," ;\n");
		break;
       case 'i':;
	      int * i;
	      i= va_arg(args,int);
              printf("%s %p %s %d %s %i %s","pointer: ",i," size: ",sizeof(*i)," value: ",*i," ;\n");
		break;
       case 'c':;
	      char *  c = va_arg(args,char);
	      printf("%s %p %s %d %s %c %s","pointer: ",c," size: ",sizeof(*c)," value: ",*c," ;\n");
		break;
	}
	
     }	
   
}
int main(int argc,const char** argv)
{
  int i=35;
  char ch='j';
  float f=7.4f;
  double d=90.543;
  char* str="string";
  Arguments("icfds",i,ch,f,d,str);
  return 0;
}
