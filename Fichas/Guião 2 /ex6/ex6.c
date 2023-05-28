#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZELINES 10
#define SIZECOL 500

void generateMatrix(int matrix[SIZELINES][SIZECOL])
{
    for (int i = 0; i < SIZELINES; i++)
    {
        for (int j = 0; j < SIZECOL; j++)
        {
            matrix[i][j] = random() % 500;
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
    int status, line = 0;
    int lines[SIZELINES];
    memset(lines,0,SIZELINES);

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
            line = 0;
            if (findNumber(matrix[i], number))
            {
                line = i;
            }
            _exit(line);
        }
    }
    
    for (int i = 0; i < SIZELINES; i++)
    {
        wait(&status);
        if (WEXITSTATUS(status) > 0)
        {
            lines[WEXITSTATUS(status)] = 1;
        }
        
    }
    
    printf("------Lines that contain number %d ------\n", number);
    for (int i = 0; i < SIZELINES; i++)
    {
        if (lines[i])
        {
            printf("Line: %d\n", i);
        }
    }
    
    return 0;
}
