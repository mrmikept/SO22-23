#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    execlp("ls","-l",NULL);
    printf("Error\n");
    return 0;
}
