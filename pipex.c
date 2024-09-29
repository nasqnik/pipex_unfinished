#include "pipex.h"

void execute(char *command, char **env)
{
    char **command_array;
    char *command_path;

    command_array = ft_split(command, ' '); 
    command_path = find_path(command_array, env);
    if (!command_array || !command_path)
        function_error("pipex: command not found"); // do we need to check with access?
    if (execve(command_path, command_array, env) == -1)
    {
        free_array(command_array);
        function_error("execve");
    }
    free_array(command_array);
}

void child_process(char **argv, int *pipefd, char **env)
{
    int file1;
    
    file1 = open_file(argv[1], 'R');
    dup2(file1, 0);
    dup2(pipefd[1], 1);
    close(pipefd[0]);
    execute(argv[2], env);
    close(file1);
}

void parent_process(char **argv, int *pipefd, char **env)
{
    int file2;

    file2 = open_file(argv[4], 'W');
    dup2(file2, 1);
    dup2(pipefd[0], 0);
    close(pipefd[1]);
    execute(argv[3], env);
    close(file2);
}

int main(int argc, char **argv, char **env)
{
    int pipefd[2];
    pid_t pid;

    if (argc == 5)
    {
        if (pipe(pipefd) == -1)
            function_error("pipe");
        pid = fork();
        if (pid == -1)
            function_error("fork");
        else if (pid == 0)
            child_process(argv, pipefd, env);
        else 
            parent_process(argv, pipefd, env);
        wait(NULL);
    }
    else
        pipex_error();
    return (0);
}

