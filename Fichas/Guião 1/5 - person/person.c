#include <sys/types.h>
#include <string.h>
#include <unistd.h> /* Chamadas ao sistema: definições e declarações essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include "person.h"

#define MAX_SIZE 256

int updateAge(const char *name, int age)
{
    int personFile;
    if ((personFile = open("personsFile", O_RDWR)) < 0)
    {
        printf("ERROR: Person file!\n");
        exit(1);
    }
    Person person = malloc(sizeof(struct person));
    while (read(personFile, person, sizeof(struct person)) > 0)
    {
        if (strcmp(person->name, name) == 0)
        {
            person->age = age;
            lseek(personFile, -sizeof(struct person), SEEK_CUR);
            write(personFile, person, sizeof(struct person));
            free(person);
            close(personFile);
            return 0;
        }
    }
    free(person);
    close(personFile);
    return 1;
}

int addPerson(const char *name, int age)
{
    int personFile;
    if ((personFile = open("personsFile", O_CREAT | O_RDWR | O_APPEND, 0640)) < 0)
    {
        printf("ERROR: Person file!\n");
        exit(1);
    }
    Person person = malloc(sizeof(struct person));
    strcpy(person->name, name);
    person->age = age;
    lseek(personFile, 0, SEEK_END);
    write(personFile, person, sizeof(struct person));
    free(person);
    close(personFile);
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        write(STDOUT_FILENO, "ERROR: No enough arguments!\n", 27);
    }

    if (strcmp(argv[1], "-i") == 0)
    {
        if (addPerson(argv[2], atoi(argv[3])) < 0)
        {
            write(STDOUT_FILENO, "ERROR ADDING PERSON!\n", 22);
            exit(1);
        }
        write(STDOUT_FILENO, "Person added successfully!\n", 27);
    }
    if (strcmp(argv[1], "-u") == 0)
    {
        if (updateAge(argv[2], atoi(argv[3])) == 1)
        {
            write(STDOUT_FILENO, "ERROR: Person not found!\n", 24);
            exit(1);
        }
        write(STDOUT_FILENO, "Age updated successfully!\n", 26);
    }
    return 0;
}
