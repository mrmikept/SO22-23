#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

void cat(int srcFd, int dstFd, ssize_t nBytes)
{
    char *buffer = malloc(sizeof(char) * nBytes);
    ssize_t bytesRead = 0;

    while ((bytesRead = read(srcFd, buffer, nBytes)) > 0)
    {
        write(dstFd, buffer, bytesRead);
    }
    free(buffer);
}


int main(int argc, char const *argv[])
{
    int srcFd = 0;
    int dstFd = 1;
    cat(srcFd,dstFd, 5000);
    return 0;
}
