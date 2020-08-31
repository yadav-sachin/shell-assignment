#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_INPUT = 1256;
const int MAX_ARG = 256;
const char* CH_DELIM = " \t\r\n\a";

void text_color_green()
{
    printf("\033[1;32m");
}

void text_color_reset()
{
    printf("\033[0m");
}

char **tokenize_line(char *line)
{
    char **args = malloc(MAX_ARG * sizeof(char *));
    char *token;
    int pos = 0;
    token = strtok(line, CH_DELIM);
    while (token != NULL)
    {
        printf("%s \n", token);
        args[pos++] = token;
        token = strtok(NULL, CH_DELIM);
    }
    return args;
}

void shell_loop()
{
    char line[MAX_INPUT];
    char **args;
    while (1)
    {
        text_color_green();
        printf("~$ ");
        text_color_reset();
        fgets(line, MAX_INPUT, stdin);
        args = tokenize_line(line);
    }
}

void shell_execute(char **args)
{
    pid_t pid = fork();

    if (pid == )
}

int main(int argc, char *argv[])
{
    system("pwd");
    shell_loop();
    return 0;
}