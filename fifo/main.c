#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


int main () {
    pid_t pid;
    char buff[100];//write buffer
        int rv;

        memset(buff, '\0', 100);
        unlink("fifo");//create fifo

        if((mkfifo("fifo", 0777)) == -1){
                printf("Can't create FIFO");
                exit(0);
        }
        //check fifo
    pid = fork();
    if (pid == 0){      //child - write
                printf("child in\n");
        int fd = open("fifo", O_WRONLY);
                if(fd == -1){
                        printf("child fifo problem");
                        exit(0);
                }

                time_t data = time(0);
                sprintf(buff, "%s", ctime(&data));
        write(fd, buff, 100);
        close(fd);

                printf("CHILD: out\n");
                exit(1);
                }
    else
        {       //parent - reader
                printf("PARENT: in\n");
                int fd = open("fifo", O_RDONLY);
                    if(fd == -1)
                    {
                            printf("parent fifo problem");
                            exit(0);
                            }

                            read(fd, buff, 100);
                            close(fd);

                            printf("PARENT: %s\n", buff);
                            printf("PARENT: out \n");
                            }
    }

