#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
    {
        write(STDOUT_FILENO,"ERROR: Error on fork!\n",22);
    }
    if (pid == 0)
    {
        execlp("ls","ls","-l",NULL);
        _exit(1);
    }
    else
    {
        wait(&status);
        if (!WEXITSTATUS(status))
        {
            write(STDOUT_FILENO,"Executed with success!\n",23);
        }
        else
        {
            write(STDOUT_FILENO,"ERROR: Error on child process!\n",31);
        }
    }
    return 0;
}
