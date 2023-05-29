#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    int status, fd[2];

    if ((pipe(fd)) < 0)
    {
        perror("ERROR: Error creating Pipe!\n");
        _exit(-1);
    }

    if ((pid = fork()) < 0)
    {
        perror("ERROR: Error using fork()!\n");
        _exit(-1);
    }
    else if(pid == 0)
    {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        close(fd[1]);
        execlp("ls","ls","/etc",NULL);
        _exit(1);
    }
    else
    {
        pid_t pidEnded = wait(&status);
        if (WIFEXITED(status))
        {
            close(fd[1]);
            dup2(fd[0],STDIN_FILENO);
            close(fd[0]);
            execlp("wc","wc","-l",NULL);
        }
        
    }
    return 0;
}
