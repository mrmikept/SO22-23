#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        printf("Missing arguments\n");
        _exit(1);
    }

    int fd = open("fifo", O_WRONLY);
    if (fd == -1)
    {
        perror("open");
    }
    else
    {
        printf("(DEBUG) opened fifo for writting\n");
    }

    write(fd, argv[1], strlen(argv[1]));

    close(fd);

    return 0;
}
