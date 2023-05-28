#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZELINES 10
#define SIZECOL 500

void generateMatrix(int matrix[SIZELINES][SIZECOL])
{
    for (int i = 0; i < SIZELINES; i++)
    {
        for (int j = 0; j < SIZECOL; j++)
        {
            matrix[i][j] = j;
        }
    }
}

int findNumber(int line[], int number)
{
    int i;
    for (i = 0; i < SIZECOL; i++)
    {
        if (line[i] == number)
        {
            return 1;
        }
        
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        write(STDOUT_FILENO,"ERROR: No input given!\n",23);
        exit(1);
    }
    int number = atoi(argv[1]);
    int matrix[SIZELINES][SIZECOL];
    pid_t pid;
    int status = 0, finding = 0;

    generateMatrix(matrix);

    for (int i = 0; i < SIZELINES; i++)
    {
        if ((pid = fork()) < 0)
        {
            write(STDOUT_FILENO,"ERROR: Error on fork()\n",23);
            exit(1);
        }
        if (pid == 0)
        {
            finding = findNumber(matrix[i], number);
            _exit(finding);
        }
    }
    
    for (int i = 0; i < SIZELINES; i++)
    {
        wait(&status);
        finding += WEXITSTATUS(status);
    }
    
    printf("Found number %d? %s!\n", number, (finding > 0 ? "Yes" : "No"));

    return 0;
}
