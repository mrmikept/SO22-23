#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 512

int main(int argc, char const *argv[])
{
    int fifo_fd;

    if ((fifo_fd = open("fifo", O_RDONLY)) < 0)
    {
        perror("ERROR: Error opening fifo!\n");
        _exit(-1);
    }

    ssize_t bytesRead;
    char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);

    while ((bytesRead = read(fifo_fd, buffer, MAX_BUFFER_SIZE)))
    {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    
    close(fifo_fd);
    return 0;
}
