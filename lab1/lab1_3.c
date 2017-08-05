#include <stdio.h>
#include <string.h>
//#include <stdarg.h>
//#define va_start( ap, parm) (ap)=(char*)(&(parm)+strlen(parm))
//#define va_arg( ap,type)  ((type*)((ap+=sizeof(type))- 1))
void Arguments(const char* format,...)
{
    char* args;
    args=format+strlen(format);
    //va_start(args,format);
    for(register unsigned int i=0;format[i];++i)
    {
       switch(format[i])
       {
       case 'd':;
	      double* ptr=// va_arg(args,double);
	                     (double*)args;
	      args+=sizeof(double);
	      printf("%s %p %s %d %s %f %s","pointer: ",ptr," size: ",sizeof(*ptr)," value: ",*ptr," ;\n");
		break;
       case 's':;
	      char **s= //va_arg(args,char*);
	                  args;
	       args+=strlen(*s);
	      printf("%s %p %s %d %s %s %s","pointer: ",s," size: ",strlen(*s)," value: ",*s," ;\n");
		break;
       case 'f':;
	 float* f=//va_arg(args,float);
	             (float*)args ;
	      args+=sizeof(float);
	      printf("%s %p %s %d %s %f %s","pointer: ",f," size: ",sizeof(*f)," value: ",*f," ;\n");
		break;
       case 'i':;
	 int*  i=//va_arg(args,int);
	         (int*)args;
	   args+=sizeof(int);
              printf("%s %p %s %d %s %i %s","pointer: ",i," size: ",sizeof(*i)," value: ",*i," ;\n");
		break;
       case 'c':;
	 char* c = //va_arg(args,char);
	           args++;
	      printf("%s %p %s %d %s %c %s","pointer: ",c," size: ",sizeof(*c)," value: ",*c," ;\n");
		break;
	}
	
     }

   
}
int main(int argc,const char** argv)
{
  int i=35;
  char ch='j';
  float f=-7.4;
  double d=-90.543;
  Arguments("cifds",ch,i,f,d,"str");
  return 0;
}
