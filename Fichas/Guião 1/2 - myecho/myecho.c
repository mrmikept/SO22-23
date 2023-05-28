#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* Chamadas ao sistema: definições e declarações essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

/**
 * Programa myecho com funcionalidade similar ao comando echo.
*/

void myecho(int srcFd, int dstFd, ssize_t bytes)
{
    char* buffer = malloc(sizeof(char) * bytes);
    ssize_t bytesRead = 0;

    while ((bytesRead = read(srcFd,buffer,bytes)) > 0)
    {
        write(dstFd, buffer, bytesRead);
    }
    free(buffer);
}

int main(int argc, char const *argv[])
{
    int srcFd = 0;
    int dstFd = 1;
    myecho(srcFd,dstFd,1024);
    return 0;
}
