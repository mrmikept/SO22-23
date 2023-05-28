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

        for (int i = 0; i < 10; i++)
        {
            write(1,"[Child] Sending number...\n",26);
            int number = i;
            sleep(1);
            write(fd[1], &number, sizeof(int));
            write(1,"[Child] Number sent!\n",21);
        }
        close(fd[1]); // Fechar descritor de escrita
        _exit(0);
    }
    else
    {
        close(fd[1]); // Fechar descritor de escrita

        ssize_t bytesRead;
        int number;
        while (bytesRead = read(fd[0], &number, sizeof(int)))
        {
            printf("[Parent] The number that my child sent is %d.\n", number);
        } 
        close(fd[0]); // Fechar descritor de leitura
        pid_t pidEnded = wait(&status);
        printf("[Parent] Child process ended with code %d.\n", WEXITSTATUS(status));
    }
    return 0;
}
