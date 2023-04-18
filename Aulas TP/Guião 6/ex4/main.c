#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
    int pd[2];
    pipe(pd);
    pid_t pid;

    if((pid = fork()) == 0)
    {
        close(pd[1]);
        dup2(pd[0], 0);
        close(pd[0]);
        execlp("wc","wc", NULL);
    }
    else
    {
        close(pd[0]);
        int bytes;
        char buffer[1024];
        while((bytes = read(0, buffer, 1024)) > 0)
        {
            write(pd[1], buffer, bytes);
        }
        close(pd[1]);
        int status;
        wait(&status);
    }
    return 0;
}
