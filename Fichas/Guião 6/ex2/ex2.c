#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int fdIn, fdOut, fdError, stdOutFd;

    stdOutFd = dup(STDOUT_FILENO);

    if ((fdIn = open("/etc/passwd", O_RDONLY)) < 0)
    {
        perror("ERROR: Error opening etc/passwd File!\n");
        _exit(-1);
    }

    if ((fdOut = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0)
    {
        perror("ERROR: Error opening saida.txt file!\n");
        _exit(-1);
    }

    if ((fdError = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0)
    {
        perror("ERROR: Error opening erros.txt file!\n");
        _exit(-1);
    }

    dup2(fdIn, STDIN_FILENO);
    close(fdIn);
    dup2(fdOut, STDOUT_FILENO);
    close(fdOut);
    dup2(fdError, STDERR_FILENO);
    close(fdError);

    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
    {
        perror("ERROR: Error on fork!\n");
        _exit(-1);
    }
    else if (pid == 0)
    {
        ssize_t bytesRead;
        char *buffer[1024];

        while ((bytesRead = read(STDIN_FILENO, buffer, 1024)) > 0)
        {
            write(STDOUT_FILENO, buffer, 1024);
            perror("This is an error!\n");
        }
        _exit(1);
    }
    else
    {
        pid_t pidEnded = wait(&status);
        if (WIFEXITED(status) && (WEXITSTATUS(status) == 1))
        {
            dup2(stdOutFd, STDOUT_FILENO);
            close(stdOutFd);

            printf("[PARENT] Terminei!\n");
        }
    }

    return 0;
}
