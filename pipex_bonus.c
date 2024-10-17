/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:03:18 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/17 14:37:09 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(int argc, char **argv, int *file2)
{
	if (argc < 6)
		pipex_error(); //maybe different error
	file2 = open_file(argv[argc - 1], 'A');
	here_doc(argv);
}

void	handle_files(int argc, char **argv, int *file1, int *file2)
{
	*file1 = open_file(argv[1], 'R');
	file2 = open_file(argv[argc - 1], 'W');
	if (dup2(file1, STDIN_FILENO) == -1)
		dup2_error(file1, NULL, "dup2 failed in main");
	close(file1);
}

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

void	middle_processes(char *cmd, char **env, int file2)
{
	pid_t	pid;
	int		pipefd[2];

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
			dup2_error(pipefd[1], file2, "dup2 failed in child_process");
		close(pipefd[1]);
		execute(cmd, env);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			dup2_error(pipefd[0], file2, "dup2 failed in parent_process");
		close(pipefd[0]);
		wait(NULL); //?
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	file1;
	int	file2;

	if (argc < 5)
		pipex_error(); // maybe different error
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		i = 3;
		handle_here_doc(argc, argv, &file2);
	}
	else
	{
		i = 2;
		handle_files(argc, argv, &file1, &file2);
	}
	while (i < argc - 2)
		middle_processes(argv[i++], env, file2);
	if (dup2(file2, STDOUT_FILENO) == -1)
		dup2_error(file2, NULL, "dup2 failed in main");
	close(file2);
	execute(argv[argc - 2], env);
	return (0);
}
