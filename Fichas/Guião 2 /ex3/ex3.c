#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    int status;

    for (int i = 1; i <= 10; i++)
    {
        if ((pid = fork()) < 0)
        {
            printf("ERROR: Error on fork!\n");
        } 
        else if(pid == 0)
        {
            printf("\n[CHILD %d]\nFather PID: %d\nMy PID: %d\n",i,getppid(),getpid());
            _exit(i);
        }
        else
        {
            pid_t terminatedPid = wait(&status);
            if (WIFEXITED(status))
            {
                printf("[FATHER]\n Terminated child: %d\n Finished code: %d\n", terminatedPid, WEXITSTATUS(status));
            }
            
        }
        
    }
    
    return 0;
}
