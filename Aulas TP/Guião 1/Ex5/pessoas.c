#include "pessoas.h"

#define FILENAME "dbfile"
struct pessoa
{
    char nome[200];
    int idade;
};

int nova_pessoa(char *nome, int idade)
{
    // Criar uma pessoa
    struct pessoa p;
    strcpy(p.nome, nome);
    p.idade = idade;

    int fd = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY, 0600);
    ssize_t r = write(fd, &p, sizeof(struct pessoa));

    if (r < 0)
    {
        perror("Error");
        return -1;
    }
    close(fd);
    return 0;
}

int atualiza_idade(char *nome, int idade)
{
    // Criar uma pessoa
    struct pessoa p;
    strcpy(p.nome, nome);
    p.idade = idade;

    int fd = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY, 0600);
    ssize_t r = write(fd, &p, sizeof(struct pessoa));

    if (r < 0)
    {
        perror("Error");
        return -1;
    }
    close(fd);
    return 0;
}