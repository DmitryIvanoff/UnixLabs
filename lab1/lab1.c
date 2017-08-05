#include <stdio.h>
#define _INTSIZEOF(n) ((sizeof(n)+sizeof(int)-1)&~(sizeof(int)-1))
typedef char * va_list;
#define va_start(ap,v) (ap=(va_list)&v+ _INTSIZEOF(v))
#define va_arg(ap,t) (t*)((ap+=_INTSIZEOF(t))-_INTSIZEOF(t))
#define va_end(ap) (ap=(va_list)0)

void Arguments(const char* format,...)
{
    va_list args;
    va_start(args,format);
    void* p;
    for(register unsigned int i=0;format[i];++i)
    {
       switch(format[i])
       {
       case 'd':;
          double* ptr= (va_arg(args,double));
	      printf("%s %p %s %d %s %f %s","pointer: ",ptr," size: ",sizeof(*ptr)," value: ",*ptr," ;\n");
		break;
       case 's':;
	      char** s;
	      s=(va_arg(args,char*));
	      printf("%s %p %s %d %s %s %s","pointer: ",s," size: ",_INTSIZEOF(*s)," value: ",*s," ;\n");
	      break;
       case 'f':;
	      double *  f ;
	      f=(va_arg(args,double));
	      printf("%s %p %s %d %s %f %s","pointer: ",f," size: ",_INTSIZEOF(*f)," value: ",*f," ;\n");
		break;
       case 'i':;
	      int*  i;
	      i=(va_arg(args,int));
	      printf("%s %p %s %d %s %i %s","pointer: ",i," size: ",sizeof(*i)," value: ",*i," ;\n");
		break;
       case 'c':;
	    char* c = (char*)(va_arg(args,char));
	 
	      printf("%s %p %s %d %s %c %s","pointer: ",c," size: ",sizeof(*c)," value: ",*c," ;\n");
		break;
	}
	
     }
va_end(args);
   
}
int main(int argc,const char** argv)
{
  int i=35;
  char ch='j';
  float f=-7.4;
  double d=-90.543;
  Arguments("fcdis",f,ch,d,i,"str");
  return 0;
}
