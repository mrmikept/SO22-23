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
    
    if (pipe(fd) < 0)
    {
        perror("ERROR: Error creating pipe!\n");
        _exit(-1);
    }
    
    if ((pid = fork()) < 0)
    {
        perror("ERROR: Error on fork()!\n");
        _exit(-1);
    }
    else if(pid == 0)
    {
       close(fd[1]);
       dup2(fd[0],STDIN_FILENO);
       close(fd[0]);
       execlp("wc","wc",NULL);
    }
    else
    {
        close(fd[0]);
        ssize_t bytesRead;
        char buffer[1024];
        while ((bytesRead = read(STDIN_FILENO,buffer,1024)) > 0)
        {
            write(fd[1],buffer,bytesRead);
        }
        close(fd[1]);
        wait(&status);
    }
    
    return 0;
}
