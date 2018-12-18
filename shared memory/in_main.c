#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/types.h>

#define FILE "Producer_main.c"

int main()
{
	char * addr;
	int mem;
	if( (mem= (shmget(2002, 32, 0666))) == -1 ){
        printf("SM open eror\n");
        exit(0);
    }

    if((addr = shmat( mem, NULL, 0 )) == (char*)-1){
		printf("SM link error\n");
        exit(0);
    }



    while(1){
        printf("%s", addr);
        sleep(1);
    }
    return 0;
}
