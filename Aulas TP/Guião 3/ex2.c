#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    __pid_t pid;

    if ((pid = fork()) == 0)
    {
        execlp("ls","-l",NULL);
        printf("Error\n");
        exit(1);
    }
    else
    {
        
    }
    
    return 0;
}
