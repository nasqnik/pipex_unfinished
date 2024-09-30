#include "pipex_bonus.h"

void execute(char *command, char **env)
{
    char **command_array;
    char *command_path;

    command_array = ft_split(command, ' '); 
    if (!command_array)
        function_error("pipex: command not found");
    command_path = find_path(command_array, env);
    if (!command_path || access(command_path, X_OK) == -1)
    {
        free_array(command_array);
        function_error("pipex: command not found");
    }
    if (execve(command_path, command_array, env) == -1)
    {
        free_array(command_array);
        function_error("execve");
    }
    free_array(command_array);
}


void pipeline(char *cmd, char **env)
{
    pid_t pid;
    int pipefd[2];

    if (pipe(pipefd) == -1)
            function_error("pipe");
    pid = fork();
    if (pid == -1)
            function_error("fork");
    else if (pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execute(cmd, env);
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
    }
}

int main(int argc, char **argv, char **env)
{
    int i;
    int file1;
    int file2;

    if (argc >= 5)
    {
        // if (ft_strcmp(argv[1], "here_doc") == 0)
        // {
        //     if (argc < 6)
        //         pipex_error(); //maybe different error
        //     fd_outfile = open_file(argv[argc - 1], 'A');
        // }
        i = 2;
        file1 = open_file(argv[1], 'R');
        file2 = open_file(argv[argc - 1], 'W');
        dup2(file1, STDIN_FILENO); //нужно сделать проверку на ошибку
        while(i < argc - 2)
            pipeline(argv[i++], env);
        dup2(file2, STDOUT_FILENO); //нужно сделать проверку на ошибку
        execute(argv[argc - 2], env);        
    }
    else
        pipex_error(); //maybe different error
    return (0);
    
}