#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h> /* Chamadas ao sistema: definições e declarações essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

/**
 * Programa mycp com funcionalidade similar ao comando cp.
*/

void mycp(int srcFd, int dstFd, ssize_t bytes)
{
    char *buffer = malloc(sizeof(char) * bytes);
    ssize_t bytesRead = 0;

    while((bytesRead = read(srcFd, buffer, bytes)) > 0)
    {
        write(dstFd, buffer, bytesRead);
    }
    free(buffer);
}


int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("ERROR: No input and/or output file paths!\n");
        return 1;
    }
    int srcFd , dstFd;
    if ((srcFd = open(argv[1],O_RDONLY)) < 0)
    {
        printf("ERROR: Input file not found!\n");
        return 1;
    }
        if ((dstFd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0600)) < 0)
    {
        printf("ERROR: Output file!\n");
        return 1;
    }
    time_t start = clock();
    mycp(srcFd, dstFd, 1024); //Quanto maior o buffer mais rapido é!
    time_t stop = clock();
    float time = (stop - start) * pow(10,-9);
    close(srcFd);
    close(dstFd);
    printf("File copied in %f!\n",time);
    return 0;
}
