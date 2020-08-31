#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include "resources/text_colors.h"
#include "resources/launch_animation.h"
#include "resources/commands.h"

const int MAX_INP = (1256);
const int MAX_ARG = 256;
const char* CH_DELIM = " \t\r\n\a";

char **tokenize_line(char *line)
{
    char **args = malloc(MAX_ARG * sizeof(char *));
    char *token;
    int pos = 0;
    token = strtok(line, CH_DELIM);
    while (token != NULL)
    {
        args[pos++] = token;
        token = strtok(NULL, CH_DELIM);
    }
    return args;
}

void shell_execute(char **args)
{
    pid_t pid = fork();
    char *command = args[0];
    if (pid < 0)
    {
        // forking was unsuccessful
    }
    else if(pid == 0)
    {
        // Inside the child process
        if (strcmp(command, "ls") == 0)
            execvp("./resources/buake_ls", args);
        else 
            execvp(args[0], args);
    }else {
        waitpid(pid, NULL, 0);
    }
}

void shell_loop()
{
    char line[MAX_INP];
    char **args;
    while (1)
    {
        text_color_green();
        printf("~$ ");
        text_color_reset();
        fgets(line, MAX_INP, stdin);
        args = tokenize_line(line);
        shell_execute(args);
    }
}

int main(int argc, char *argv[])
{
    launch_animation();
    shell_loop();
    return 0;
}