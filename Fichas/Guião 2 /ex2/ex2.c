#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    
    if ((pid = fork()) < 0)
    {
        printf("ERROR: Error on fork()!");
    } 
    else if(pid == 0)
    {
        printf("\n[Child]\nParent PID: %d\nMy PID: %d\n",getppid(),getpid());
        _exit(0);
    }
    else
    {
        printf("[Parent]\nParent PID: %d\nMy PID: %d\nChild PID: %d\n",getppid(), getpid(), pid);
    }
    

    return 0;
}
