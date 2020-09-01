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

void shell_execute_fork(char **args)
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
        else if(strcmp(command, "grep") == 0)
            execvp("./resources/buake_grep", args);
        else if(strcmp(command, "cat") == 0)
            execvp("./resources/buake_cat", args);
        else if(strcmp(command, "mv") == 0)
            execvp("./resources/buake_mv", args);
        else if(strcmp(command, "cp") == 0)
            execvp("./resources/buake_cp", args);
        else if(strcmp(command, "rm") == 0)
            execvp("./resources/buake_rm", args);
        else 
            execvp(args[0], args);
    }else {
        waitpid(pid, NULL, 0);
    }
}

void buake_cd(char **args)
{
    char *path = args[1];
    if (path)
    {
        int status = chdir(path);
        if (status != 0)
        {
            text_color_red();
            printf("cd: no such file or directory: %s\n", path);
            text_color_reset();
        }
    }
    else chdir("/");
}

void buake_pwd()
{
    char curr_dir[MAX_INP];
    if ( getcwd(curr_dir, sizeof(curr_dir)) != NULL)
        printf("%s\n", curr_dir);   
    else {
        text_color_red();
        printf("Current Directory Info Denied\n");
        text_color_reset();
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
    char line[MAX_INP];
    char **args;
    char cwd[MAX_INP];
    while (1)
    {
        text_color_magenta();
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("~%s :", cwd);
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