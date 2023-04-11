#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_LINE_SIZE 1024

int main(int argc, char const *argv[])
{
    char buf[MAX_LINE_SIZE];
    int bytes_read, fd;

    if((fd = open("fifo", O_WRONLY, 0600)) == -1)
    {
        perror("open");
    }
    else
    {
        printf("opened fifo for writing\n");
    }

    while ((bytes_read = read(0, buf, MAX_LINE_SIZE)) > 0)
    {
        write(fd, buf, bytes_read);
    }
    
    close(fd);
    return 0;
}
