#include "pipex.h"

void file_error(char *filepath)
{
    ft_printf("Error %s: ", filepath);
    ft_printf("%s\n", strerror(errno));
    //try perror(""); instead the upper line
    exit(EXIT_FAILURE);
}

void function_error(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}


void pipex_error(void)
{
    ft_printf("Incorrect amount of arguments\n");
    ft_printf("The correct usage: ./pipex file1 cmd1 cmd2 file2\n");
    exit(EXIT_FAILURE);
}