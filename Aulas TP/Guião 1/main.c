#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd = open("out", O_CREAT | O_RDWR, 0600);

    int i1 = 60;
    int i2 = 123456;

    write(fd, &i1, sizeof(int));
    write(fd, &i2, sizeof(int));

    lseek(fd, -2*sizeof(int), SEEK_CUR);
    // lseek(fd,0, SEEK_SET);

    int i3;
    int i4;

    read(fd, &i3, sizeof(int));
    read(fd, &i4, sizeof(int));

    printf("%d %d\n", i3, i4);

    close(fd);

    return 0;
}