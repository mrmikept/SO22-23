#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    int status;
    pid_t pids[argc-1];

    for (int i = 1; i < argc; i++)
    {
        if((pid = fork()) < 0)
        {
            perror("ERROR: Error on fork!\n");
        }
        else if (pid == 0)
        {
            int exec_return = execlp(argv[i],argv[i],NULL);
            _exit(0);
        }
        else
        {
            pids[i - 1] = pid;
        }
    }
    
    for (int i = 0; i < argc - 1; i++)
    {
        pid_t terminated_pid = waitpid(pids[i], &status,0);
        if (WIFEXITED(status))
        {
            printf("[Father] Child %d executed succesfully!\n",terminated_pid);
        }
    }
    return 0;
}
