#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define MAX_LINE_SIZE 1024

int main(int argc, char const *argv[])
{
    int fd;
    int bytes_read;
    char buf[MAX_LINE_SIZE];

    if((fd = open("fifo", O_RDONLY, 0600)) == -1)
    {
        perror("open");
        return -1;
    }
    else
    {
        printf("opened fifo for reading\n");
    }

    while ((bytes_read = read(fd, &buf, MAX_LINE_SIZE)) > 0)
    {
        write(1, &buf, bytes_read);
    }

    printf("done\n");

    close(fd);
    unlink("fifo");
    

    return 0;
}
