/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:45 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/17 14:34:42 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# include <unistd.h> // access
# include <stdio.h> // perror
# include <fcntl.h> // open
# include <string.h> // strerror
# include <errno.h> 
# include <sys/types.h>
# include <sys/wait.h>

// pipex_bonus_utils.c
int		open_file(char *filepath, char mode);
char	*find_path(char **command_array, char **env);
char	*ft_getenv(char *key, char **env);
void	free_array(char **array);
void	close_pipe_ends(int *pipefd);

// pipex_errors.c
void	file_error(char *filepath, int *pipefd, int flag);
void	function_error(char *message, int *pipefd, int flag);
void	pipex_error(void);
void	cmd_check_error(char *cmd, int fd, int *pipefd);
void	exec_error(char *command_path, char **command_array, char *msg);

// pipex_more_errors.c
void	dup2_error(int fd1, int fd2, char *msg);

//pipex_here_doc.c
void	here_doc_input(char **argv, int *pipefd);
void	here_doc(char **argv);

#endif