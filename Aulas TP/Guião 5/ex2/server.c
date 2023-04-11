#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    // create fifo
    if(mkfifo("fifo", 0666) == -1)
    {
        perror("mkfifo");
    }

    // TODO exit

    while(1)
    {
        if(fd = open("fifo", O_RDONLY))
        {
            perror("open");
            return -1;
        }
        else
        {
            printf("[DEBUG] opened fifo for reading\n");
        }

        while ((bytes_read = read(fd, buf, MAX_ARG_SIZE)) > 0)
        {
            
        }
        {
            /* code */
        }
        
    }

    return 0;
}
