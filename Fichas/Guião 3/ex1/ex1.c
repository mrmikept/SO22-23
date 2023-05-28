#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
   int exec_return = execlp("ls","ls","-l",NULL);
   printf("IF YOU SEE THIS SOMETHING IS VERY WRONG!\n"); //This is not printed because the program is changed by ls.
   return 0;
}