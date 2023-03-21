#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    __pid_t pid;

    if ((pid = fork()) == 0)
    {
        execlp("ls", "ls", "--color", NULL);
        printf("error\n");
        exit(1);
    }
    else
    {
        int status;
        __pid_t terminated = wait(&status);
        if(WIFEXITED(status))
        {
            int code = WEXITSTATUS(status);
            printf("child %d terminated with exit code %d\n", terminated, code);
        }
        else
        {
            printf("error\n");
        }
    }

    return 0;
}