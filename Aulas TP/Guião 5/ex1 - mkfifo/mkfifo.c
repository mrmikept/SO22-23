#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    mkfifo("fifo",0600);
    printf("Pipe com nome: 'fifo' criado!\n");
    return 0;
}
