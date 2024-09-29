#include "pipex.h"

void file_error(char *filepath)
{
    ft_printf("pipex: %s: ", filepath);
    ft_printf("%s\n", strerror(errno));
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

void cmd_check_error(char *cmd)
{
    if (ft_strcmp(cmd, "") == 0)
    {
        ft_printf("pipex: : command not found\n");
        exit(EXIT_FAILURE);
    }
}