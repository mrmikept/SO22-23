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

    if ((fifo_fd = open("fifo", O_WRONLY)) < 0)
    {
        perror("ERROR: Error opening fifo!\n");
        _exit(-1);
    }

    char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    ssize_t bytesRead;

    while ((bytesRead = read(STDIN_FILENO, buffer, MAX_BUFFER_SIZE)) > 0)
    {
        write(fifo_fd, buffer, bytesRead);
    }
    
    close(fifo_fd);

    return 0;
}
