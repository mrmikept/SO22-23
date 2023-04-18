#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

void mycp(int srcFd, int dstFd, ssize_t nBytes)
{
    char *buffer = malloc(sizeof(char) * nBytes);
    ssize_t bytesRead = 0;

    while ((bytesRead = read(srcFd, buffer, nBytes)) > 0)
    {
        write(dstFd, buffer, bytesRead);
    }
    
}

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        printf("Falta Argumentos!\n Insira <srcfile> <dstfile>");
        exit(1);
    }

    int srcFd = open(argv[1], O_RDONLY);
    int dstFd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0600);

    mycp(srcFd, dstFd, 4064);

    close(srcFd);
    close(dstFd);

    return 0;
}
