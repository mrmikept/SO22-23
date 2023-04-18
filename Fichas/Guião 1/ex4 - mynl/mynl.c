#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

/////////
// WIP //
/////////

#define MAX_BUFFER_SIZE 1024

ssize_t readln(int srcFd, char *linha, size_t bytes)
{
    int i = 0;
    ssize_t bytesRead = 0;
    char c;

    while(i < bytes && (bytesRead = read(srcFd, &c, 1)) > 0 && linha[i] != '\n')
    {
        linha[i++] = c;
    }

    return i;
}


int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        printf("Faltam argumentos! Insira ficheiro de input!\n");
        exit(1);
    }

    int srfd;
    if((srfd = open(argv[1], O_RDONLY, 0600)) < 0)
    {
        printf("Problema a abrir descritor do ficheiro de input!\n");
        exit(1);
    }


    ssize_t length;

    char *linha = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    int lineNr = 1;
    while ((length = readln(srfd, linha, MAX_BUFFER_SIZE)))
    {   
        printf("%d ",lineNr);
        write(1, linha, length);
        lineNr++;
    }
    
    close(srfd);
    return 0;
}
