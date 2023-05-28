#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd[2], status;
    pid_t pid;

    if ((pipe(fd)) < 0)
    {
        perror("ERROR: Error creating pipe!\n");
        _exit(-1);
    }

    if ((pid = fork()) < 0)
    {
        perror("ERROR: Error on fork()!\n");
    }
    else if (pid == 0)
    {
        close(fd[0]); // Fechar descritor de leitura
        int number = 45;
        write(fd[1], &number, sizeof(int));
        close(fd[1]); // Fechar descritor de escrita
        _exit(0);
    }
    else
    {
        close(fd[1]); // Fechar descritor de escrita
        pid_t pidEnded = wait(&status);
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) == 0)
            {
                ssize_t bytesRead;
                int number;
                while ((bytesRead = read(fd[0], &number, sizeof(int))) > 0)
                {
                    printf("[Parent] The number that my child sent is %d.\n", number);
                }
                close(fd[0]); // Fechar descritor de leitura
                
            }
            printf("[Parent] Child process ended with code %d.\n", WEXITSTATUS(status));
        }
    }
    return 0;
}
