#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int in = open("/etc/passwd", O_RDONLY, 0600);
    int out = open("saida.txt", O_CREAT | O_WRONLY, 0600);
    int err = open("errors.txt", O_CREAT | O_WRONLY, 0600);
    int original_stdout = dup(1); // Para guardar o apontador para o terminal, de modo a poder fazer print de "terminei".


    dup2(in, 0); //O dup2 faz a copia de um descritor para outro descritor
    close(in);
    dup2(out, 1);
    close(out);
    dup2(err, 2);
    close(err);

    ssize_t bytes;
    char *buffer[1024];
    while ((bytes = read(0, buffer, 1024)) > 0)
    {
        write(1, buffer, bytes);
    }

    dup2(original_stdout, 1);
    close(original_stdout);

    printf("terminei\n");

    return 0;
}
