#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

ssize_t readln(int fd, char *line, size_t size)
{
    char c;
    __ssize_t pos = 0;

    int i = 0;
    while (read(fd, &c, size) > 0)
    {
        line[pos++] = c;

        if (c == '\n')
        {
            break;
        }
    }

    return pos;
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Missing arguments!\n");
        exit(1);
    }
    int srcFd = open(argv[1], O_RDONLY);
    char *line = malloc(sizeof(char) * 100);
    ssize_t lenght = readln(srcFd, line, 1); // Quanto maior o buffer mais rápido é!

    printf("line: %s\nbytes: %ld\n", line, lenght);
    close(srcFd);
    return 0;
}
