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
    pid_t pids[4];
    int fd[3][2], status;
    for (int i = 0; i < 3; i++)
    {
        if ((pipe(fd[i])) < 0)
        {
            perror("ERROR: Error creating pipe!\n");
            _exit(-1);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if ((pid = fork()) < 0)
        {
            perror("ERROR: Error on fork!\n");
            _exit(-1);
        }

        if (i == 0 && pid == 0) // Grep
        {
            close(fd[0][0]);
            dup2(fd[0][1], STDOUT_FILENO);
            close(fd[0][1]);
            for (int j = 1; j < 3; j++)
            {
                close(fd[j][0]);
                close(fd[j][1]);
            }
            execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
            _exit(1);
        }
        else if (i == 1 && pid == 0) // cut
        {
            close(fd[0][1]);               // Fechar o descritor de escrita do pipe anterior
            dup2(fd[0][0], STDIN_FILENO);  // Substituir o StdInput pelo descritor de leitura do pipe anterior
            close(fd[0][0]);               // Fechar o descritor de leitura do pipe anterior
            close(fd[1][0]);               // Fechar o descritor de leitura do pipe atual
            dup2(fd[1][1], STDOUT_FILENO); // Substituir o StdOutput pelo descritor de escrita do pipe atual
            close(fd[1][1]);               // Fechar o descritor de escrita do pipe atual
            for (int j = 0; j < 3; j++)
            {
                if (j != i - 1 && j != i)
                {
                    close(fd[j][0]);
                    close(fd[j][1]);
                }
            }
            execlp("cut", "cut", "-f7", "-d:", NULL);
            _exit(1);
        }
        else if (i == 2 && pid == 0) // uniq
        {
            close(fd[1][1]);
            dup2(fd[1][0], STDIN_FILENO);
            close(fd[1][0]);
            close(fd[2][0]);
            dup2(fd[2][1], STDOUT_FILENO);
            close(fd[2][1]);
            for (int j = 0; j < 2; j++)
            {
                if (j != i - 1 && j != i)
                {
                    close(fd[j][0]);
                    close(fd[j][1]);
                }
            }
            execlp("uniq", "uniq", NULL);
            _exit(1);
        }
        else if (i == 3 && pid == 0) // wc -l
        {
            close(fd[2][1]);
            dup2(fd[2][0], STDIN_FILENO);
            close(fd[2][0]);
            close(fd[3][0]);
            dup2(fd[3][1], STDOUT_FILENO);
            close(fd[3][1]);
            for (int j = 0; j < 4 - 2; j++)
            {
                close(fd[j][0]);
                close(fd[j][1]);
            }
            execlp("wc", "wc", "-l", NULL);
            _exit(1);
        }
        else
        {
            pids[i] = pid;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        close(fd[i][0]);
        close(fd[i][1]);
    }

    for (int i = 0; i < 4; i++)
    {
        pid_t pidEnded = wait(&status);
        if (WEXITSTATUS(status) < 0)
        {
            perror("Error: Something went wrong!\n");
            _exit(-1);
        }
        else
            write(STDOUT_FILENO,"[Father] Child done!\n",21);
    }
    return 0;
}
