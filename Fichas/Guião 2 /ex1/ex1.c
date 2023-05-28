#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
    printf("Father PID: %d\n Child PID: %d\n",getppid(),getpid());
    return 0;
}
