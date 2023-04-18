#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define MAX_ARG_SIZE 1024

int main(int argc, char const *argv[])
{
    char buf[MAX_ARG_SIZE];
    int bytes_read;
    int logfile, fd, fd2;

    //logfile
    if((logfile = open("log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666)) == -1)
    {
        perror("open");
        return -1;
    }

    // create fifo
    if (mkfifo("fifo", 0666) == -1)
    {
        perror("mkfifo");
    }

    //open fifo for reading
    if (fd = open("fifo", O_RDONLY) == -1)
    {
        perror("open");
        return -1;
    }
    else
    {
        printf("[DEBUG] opened fifo for reading\n");
    }

    // open fifo for writing
    // (to avoid exiting when there are no clients)
    if ((fd2 = open("fifo", O_WRONLY)) == -1)
    {
        perror("open");
        return -1;
    }

    // read from fifo
    // TODO: sair quando receber "exit"
    while ((bytes_read = read(fd, buf, MAX_ARG_SIZE)) > 0)
    {
        write(logfile, buf, bytes_read);
        buf[bytes_read] = '\0';
        printf("[DEBUG] wrote %s to file \n", buf);
    }

    write(logfile, "\n\0", 1);
    printf("(DEBUG) EDF\n");
    close(fd);
    close(logfile);
    unlink("fifo");
    return 0;
}
