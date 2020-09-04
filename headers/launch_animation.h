void launch_animation()
{
    FILE *launch_file = fopen("resources/launch_text.txt", "r");
    char ch;
    text_color_cyan();
    ch = fgetc(launch_file);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(launch_file);
        for (int i = 0; i < 500000; ++i) ;
    }
    text_color_reset();
}