#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
    int in = open("/etc/passwd", O_RDONLY, 0600);
    int out = open("saida.txt", O_CREAT | O_WRONLY, 0600);
    int err = open("errors.txt", O_CREAT | O_WRONLY, 0600);
    int original_stdout = dup(1); // Para guardar o apontador para o terminal, de modo a poder fazer print de "terminei".

    dup2(in, 0); // dtdin now becomes "in"
    close(in);
    dup2(out, 1); // stdout now becomes "out"
    close(out);
    dup2(err, 2); // stderr now becomes "err"
    close(err);

    if (fork() == 0)
    {
        execlp("wc", "wc", NULL);
        perror("wc");
    }

    int status;
    wait(&status);

    if (!WIFEXITED(status))
    {
        printf("error\n");
    }

    printf("INTRUSER!");

    dup2(original_stdout, 1);
    close(original_stdout);

    printf("terminei\n");

    return 0;
}
