#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int pd[2], status;
    pid_t pid;

    if (pipe(pd) < 0)
    {
        perror("ERROR: Error creating pipe!\n");
        _exit(-1);
    }

    if ((pid = fork()) < 0)
    {
        perror("ERROR on fork!\n");
        _exit(-1);
    }
    else if (pid == 0)
    {
        close(pd[1]);
        ssize_t bytesRead;
        int number;
        while ((bytesRead = read(pd[0],&number,sizeof(int))))
        {
            printf("[CHILD] The number that my parent sent is %d\n",number);
        }
        close(pd[0]);
        _exit(0);
    }
    else
    {
        int number = 35;
        close(pd[0]);
        sleep(5);
        write(pd[1],&number,sizeof(int));
        close(pd[1]);
        pid_t pidEnded = wait(&status);
        printf("[Parent] Child process ended with code %d\n", WEXITSTATUS(status));
    }
    return 0;
}
