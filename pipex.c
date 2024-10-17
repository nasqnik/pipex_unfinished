/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:07 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/17 12:53:53 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *command, char **env)
{
	char	**command_array;
	char	*command_path;

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
		exec_error(command_path, command_array, "pipex: command not found");
	if (execve(command_path, command_array, env) == -1)
		exec_error(command_path, command_array, "execve");
}

void	child_process(char **argv, int *pipefd, char **env)
{
	int	file1;

	file1 = open_file(argv[1], 'R', pipefd);
	cmd_check_error(argv[2], file1, pipefd);
	close(pipefd[0]);
	if (dup2(file1, STDIN_FILENO) == -1 || dup2(pipefd[1], STDOUT_FILENO) == -1)
		dup2_error(file1, pipefd[1], "dup2 failed in child_process");
	close(file1);
	close(pipefd[1]);
	execute(argv[2], env);
}

void	parent_process(char **argv, int *pipefd, char **env)
{
	int	file2;

	file2 = open_file(argv[4], 'W', pipefd);
	cmd_check_error(argv[3], file2, pipefd);
	close(pipefd[1]);
	if (dup2(file2, STDOUT_FILENO) == -1 || dup2(pipefd[0], STDIN_FILENO) == -1)
		dup2_error(file2, pipefd[0], "dup2 failed in parent_process");
	close(file2);
	close(pipefd[0]);
	execute(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
		pipex_error();
	if (pipe(pipefd) == -1)
		function_error("pipe", pipefd, 1);
	pid = fork();
	if (pid == -1)
		function_error("fork", pipefd, 1);
	else if (pid == 0)
		child_process(argv, pipefd, env);
	else
	{
		parent_process(argv, pipefd, env);
		wait(NULL);
	}
	return (0);
}
