#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd = open("fifo", O_RDONLY, 0600);
    printf("fifo open\n");
    int x;
   while(read(fd, &x, sizeof(int)) > 0)
   {
    printf("read: %d\n", x);
   }
   printf("done\n");
   close(fd);
    return 0;
}
