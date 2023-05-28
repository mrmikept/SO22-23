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
            printf("ERROR: Error on fork()!\n");
        }
        if (pid == 0) // Child Process
        {
            printf("\n[CHILD %d]\nMy father PID: %d\nMy PID: %d\n",i,getppid(), getpid());
            _exit(i);
        }
    }
    
    for (int i = 1; i <= 10; i++)
    {
        pid_t terminatedPid = wait(&status);
        printf("[FATHER] Child %d finished! | Exit code: %d\n",terminatedPid,WEXITSTATUS(status));
    }

    return 0;
}
