#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "pessoas.h"

int main(int argc, char const *argv[])
{
    if(strcmp(argv[1], "-i") == 0)
    {
        nova_pessoa(argv[2], atoi(argv[3]));
    }

    if(strcmp(argv[1], "-u") == 0)
    {
        atualiza_idade(argv[2], atoi(argv[3]));
    }

    return 0;
}