#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

//writer
int main(int argc, char const *argv[])
{
    if(mkfifo("fifo",0600) == -1)
    {
        perror("mkfifo");
    }

    int fd = open("fifo", O_WRONLY, 0600);
    printf("fifo open\n");
    int x1 = 65;
    int x2 = 66;

    write(fd, &x1, sizeof(int));
    write(fd, &x2, sizeof(int));

    printf("done\n");
    close(fd);
    unlink("fifo");

    return 0;
}
