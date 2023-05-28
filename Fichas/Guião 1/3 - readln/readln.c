#include <sys/types.h>
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

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        printf("ERROR: No input file path!\n");
        exit(1);
    }

    int srcFd;
    if ((srcFd = open(argv[1], O_RDONLY)) < 1)
    {
        printf("ERROR: Input file not found!\n");
        exit(1);
    }
    
    char* line = malloc(sizeof(char) * 100);
    ssize_t length = readln(srcFd, line, 1);

    printf("Line: %sNumber of bytes = %ld\n",line, length);
    free(line);

    close(srcFd);
    return 0;
}
