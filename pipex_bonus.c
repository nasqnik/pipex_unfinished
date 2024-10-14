/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:03:18 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/14 15:16:09 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void here_doc_input(char **argv, int *pipefd)
{
    char *input;
    
    close(pipefd[0]);
    input = get_next_line(0);
    while (input != NULL)
    {
        if (ft_strncmp(input, argv[2], ft_strlen(argv[2])) == 0)
        {
            free(input);
            exit(0); 
        }
        ft_putstr_fd(input, pipefd[1]);
        free(input);
        input = get_next_line(0);
    }
}

void here_doc(char **argv)
{
    pid_t pid;
    int pipefd[2];

    if (pipe(pipefd) == -1)
        function_error("pipe", pipefd, 1);
    pid = fork();
    if (pid == -1)
        function_error("fork", pipefd, 1);
    else if (pid == 0)
        here_doc_input(argv, pipefd);
    else
    {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            close(pipefd[0]);
            function_error("dup2 failed in parent_process", NULL, 0);
        }
        close(pipefd[0]);
        wait(NULL);
    }
}

void execute(char *command, char **env)
{
    char **command_array;
    char *command_path;

    if (command[0] != '/')
    {
        command_array = ft_split(command, ' '); 
        if (!command_array)
            function_error("pipex: command not found", NULL, 0);
        command_path = find_path(command_array, env);
    }
    else
    {
        command_array = malloc(2 * sizeof(char *));
        command_path = ft_strdup(command);
        command_array[0] = ft_strdup(command);
        command_array[1] = NULL;
    }
    if (!command_path || access(command_path, X_OK) == -1)
    {
        if (command_path)
            free(command_path);
        free_array(command_array);
        function_error("pipex: command not found", NULL, 0);
    }
    if (execve(command_path, command_array, env) == -1)
    {
        free(command_path);
        free_array(command_array);
        function_error("execve", NULL, 0);
    }
}


void middle_processes(char *cmd, char **env, int file2)
{
    pid_t pid;
    int pipefd[2];

    if (pipe(pipefd) == -1)
        function_error("pipe", pipefd, 1);
    cmd_check_error(cmd, file2, pipefd);
    pid = fork();
    if (pid == -1)
        function_error("fork", pipefd, 1);
    else if (pid == 0)
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            close(pipefd[1]);
            close(file2);
            function_error("dup2 failed in child_process", NULL, 0);
        }
        close(pipefd[1]);
        execute(cmd, env);
    }
    else
    {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            close(pipefd[0]);
            close(file2);
            function_error("dup2 failed in parent_process", NULL, 0);
        }
        close(pipefd[0]);
        wait(NULL); //?
    }
}

int main(int argc, char **argv, char **env)
{
    int i;
    int file1;
    int file2;

    if (argc >= 5)
    {
        if (ft_strcmp(argv[1], "here_doc") == 0)
        {
            if (argc < 6)
                pipex_error(); //maybe different error
            i = 3;
            file2 = open_file(argv[argc - 1], 'A');
            here_doc(argv);
        }
        else
        {
            i = 2;
            file1 = open_file(argv[1], 'R');
            file2 = open_file(argv[argc - 1], 'W');
            if (dup2(file1, STDIN_FILENO) == -1)
            {
                close(file1);
                function_error("dup2 failed in main", NULL, 0);
            }
            close(file1);
        }
        while (i < argc - 2)
                middle_processes(argv[i++], env, file2);
        if (dup2(file2, STDOUT_FILENO) == -1)
        {
            close(file2);
            function_error("dup2 failed in main", NULL, 0);
        }
        close(file2);
        execute(argv[argc - 2], env);           
    }
    else
        pipex_error(); // maybe different error
    return (0);    
}
