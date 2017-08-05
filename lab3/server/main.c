#include "incld.h"
//server
int main(int argc,const char** argv)
{
    int dd;
	//создаем дверь и связываем ее с ф-ей server_proc
	dd = door_create(server_proc, NULL, 0 );           
	unlink(DOORNAME);                                
	close( open(DOORNAME, O_CREAT|O_RDWR, 0660 ));    
	fattach( dd, DOORNAME );
	//ждем
    for(;;)
    pause();		
}