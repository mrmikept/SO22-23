#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#ifdef PERSON_H
#define PERSON_H
int nova_pessoa(char *nome, int idade);
int atualiza_idade(char *nome, int idade);
#endif

