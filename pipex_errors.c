/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:52 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/17 12:56:25 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_error(char *filepath, int *pipefd, int flag)
{
	if (flag == 1 && pipefd != NULL)
		close_pipe_ends(pipefd);
	ft_printf("pipex: %s: ", filepath);
	ft_printf("%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

void	function_error(char *message, int *pipefd, int flag)
{
	if (flag == 1 && pipefd != NULL)
		close_pipe_ends(pipefd);
	perror(message);
	exit(EXIT_FAILURE);
}

void	pipex_error(void)
{
	ft_printf("Incorrect amount of arguments\n");
	ft_printf("The correct usage: ./pipex file1 cmd1 cmd2 file2\n");
	exit(EXIT_FAILURE);
}

void	cmd_check_error(char *cmd, int fd, int *pipefd)
{
	if (ft_strcmp(cmd, "") == 0)
	{
		close(fd);
		close_pipe_ends(pipefd);
		ft_printf("pipex: : command not found\n");
		exit(EXIT_FAILURE);
	}
}

void	exec_error(char *command_path, char **command_array, char *msg)
{
	if (command_path)
		free(command_path);
	if (command_array)
		free_array(command_array);
	function_error(msg, NULL, 0);
}
