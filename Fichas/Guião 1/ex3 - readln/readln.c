#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

ssize_t readln(int srcFd, char *linha, size_t bytes)
{
    int size = 0;
    ssize_t bytesRead = 0;
    char c;

    while (size < bytes && (bytesRead = read(srcFd, &c, 1)) > 0)
    {
        linha[size++] = c;
        if (c == '\n')
        {
            break;
        }
    }

    return size;
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Faltam argumentos! Insira ficheiro de input!\n");
        exit(1);
    }

    int srfd;
    if ((srfd = open(argv[1], O_RDONLY, 0600)) < 0)
    {
        printf("Problema a abrir descritor do ficheiro de input!\n");
        exit(1);
    }

    ssize_t length;

    char *linha = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    
    //Ler apenas uma linha do ficheiro.
    // length = readln(srfd, linha, MAX_BUFFER_SIZE);
    // write(1, linha, length);

    //Ler todas as linhas do ficheiro
    while ((length = readln(srfd, linha, MAX_BUFFER_SIZE)) > 0)
    {   
        write(1, linha, length);
    }


    close(srfd);
    return 0;
}
