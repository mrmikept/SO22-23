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
    int fifo, fifo_fd, logs_fd;

    if ((fifo = mkfifo("fifo",0600)) < 0)
    {
        perror("ERROR: Error creating fifo!\n");
        _exit(-1);
    }

    if ((fifo_fd = open("fifo", O_RDONLY)) < 0)
    {
        perror("ERROR: Error opening fifo!\n");
        _exit(-1);
    }

    if ((logs_fd = open("logs", O_WRONLY | O_CREAT | O_APPEND, 0640)) < 0)
    {
        perror("ERROR: Error opening logs file!\n");
        _exit(-1);
    }

    char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    ssize_t bytesRead;
    
    while((bytesRead = read(fifo_fd, buffer, MAX_BUFFER_SIZE)) > 0)
    {
        write(logs_fd, buffer, bytesRead);
    }

    close(fifo_fd);
    close(logs_fd);
    unlink(fifo);

    return 0;
}
