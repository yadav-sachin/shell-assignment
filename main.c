#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

const int MAX_INP = (1256);
const int MAX_ARG = 256;
const char* CH_DELIM = " \t\r\n\a";

#include "headers/text_colors.h"
#include "headers/launch_animation.h"
#include "headers/commands.h"


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

void shell_execute_fork(char **args)
{
    int background_flag = 0;
    for (int i = 0; args[i] != NULL; ++i)
    {
        if (strcmp(args[i], "&") == 0)
        {
            background_flag = 1;
            args[i] = NULL;
            break;
        }
    }
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
            execvp("./bin/buake_ls", args);
        else if(strcmp(command, "grep") == 0)
            execvp("./bin/buake_grep", args);
        else if(strcmp(command, "cat") == 0)
            execvp("./bin/buake_cat", args);
        else if(strcmp(command, "mv") == 0)
            execvp("./bin/buake_mv", args);
        else if(strcmp(command, "cp") == 0)
            execvp("./bin/buake_cp", args);
        else if(strcmp(command, "rm") == 0)
            execvp("./bin/buake_rm", args);
        else if(strcmp(command, "mkdir") == 0)
            execvp("./bin/buake_mkdir", args);
        else 
            execvp(args[0], args);
    }else {
        if (background_flag == 0)
            waitpid(pid, NULL, 0);
    }
}

void shell_execute(char **args)
{
    char *command = args[0];
    if ( strcmp(command, "cd") == 0)
        buake_cd(args);
    else if( strcmp(command, "pwd") == 0)
        buake_pwd();
    else 
        shell_execute_fork(args);
}

void shell_loop()
{
    char line[MAX_INP], user[MAX_INP], cwd[MAX_INP], host[MAX_INP];
    char **args;
    while (1)
    {
        text_color_green();
        getlogin_r(user, MAX_INP);
        gethostname(host, MAX_INP);
        printf("%s@%s:", user, host);
        text_color_blue();
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("~%s:", cwd);
        text_color_green();
        printf(">$");
        text_color_reset();
        printf(" ");
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