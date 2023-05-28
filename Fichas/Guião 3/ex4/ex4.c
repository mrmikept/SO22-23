#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mySystem(char *commandLine)
{
    char *args[50];
    pid_t pid, pid_ended;
    int status, i, exec_return;
    char *command = strtok(commandLine, " ");
    for (i = 0; command != NULL; i++)
    {
        args[i] = command;
        command = strtok(NULL, " ");
    }
    args[i] = NULL;
    
    if ((pid = fork()) < 0)
    {
        perror("ERROR: Error on fork!");
        _exit(-1);
    }
    else if (pid == 0) // Child Process
    {
        exec_return = execvp(args[0], args);
        _exit(1);
    }
    else // Parent Process
    {
        pid_ended = wait(&status);
        if (WIFEXITED(status))
        {
            printf("Child process, with PID %d, exited with code %d.\n",pid_ended, WEXITSTATUS(status));
            return exec_return;
        }
        else return -1;
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        perror("No input inserted!\n");
        exit(1);
    }

    char command[100];
    for (int i = 1; i < argc; i++)
    {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    int systemReturn = mySystem(command);
    printf("System function terminated with code %d\n", systemReturn);

    return 0;
}
