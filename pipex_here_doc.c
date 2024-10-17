/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:30:05 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/17 14:39:49 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_input(char **argv, int *pipefd)
{
	char	*input;

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

void	here_doc(char **argv)
{
	pid_t	pid;
	int		pipefd[2];

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
