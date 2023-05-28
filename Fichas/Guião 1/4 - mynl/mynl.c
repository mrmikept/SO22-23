#include <sys/types.h>
#include <string.h>
#include <unistd.h> /* Chamadas ao sistema: definições e declarações essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h> 

ssize_t readln(int srcFd, char *line, size_t bytes)
{
    char c;
    ssize_t nrBytes = 0;

    while (read(srcFd, &c, bytes) > 0)
    {
        line[nrBytes++] = c;
        if (c == '\n')
        {
            break;
        }
    }
    return nrBytes;
}

void mynl(int srcFd, ssize_t bytes)
{
    int i = 1;
    char *line = malloc(sizeof(char) * 1024);
    char *newLine = malloc(1024);
    ssize_t length = 0;
    while ((length = readln(srcFd, line, 1)) > 0)
    {
        sprintf(newLine, "%d %s", i, line);
        write(STDOUT_FILENO, newLine, length + 2);
        i++;
    }
    
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("ERROR: Input file path not found!\n");
        exit(1);
    }

    int srcFd;
    if ((srcFd = open(argv[1], O_RDONLY)) < 0)
    {
        printf("ERROR: Input file!\n");
        exit(1);
    }
    mynl(srcFd, 1024);

    close(srcFd);
    return 0;
}
