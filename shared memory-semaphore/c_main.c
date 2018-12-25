#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#define FILE "makefile"

struct sembuf sem_lock = {0,-1,0}, sem_open = {0,1,0};

int main()
{
        char * addr;
        key_t semkey = ftok("/tmp", 'a');
        int X=1, shmid = (shmget(2066, 32, 0666));
        int semid = (semget(semkey, 1, 0666));
        if(semid == -1){
                printf("Sem err\n");
                exit(0);
        }

        if( shmid == -1 ){
                printf("SM err\n");
                exit(0);
        }

        if((addr = shmat( shmid, NULL, 0 )) == (char*)-1){
                printf("SMat err\n");
                exit(0);
        }



        while(X){
                semop(semid, &sem_lock, 1);
                printf("%s", addr);
                semop(semid, &sem_open, 1);
				sleep(10);
        }
        return 0;
}
