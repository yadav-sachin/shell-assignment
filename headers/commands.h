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