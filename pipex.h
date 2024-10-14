/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:14 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/14 15:26:16 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# include <unistd.h> // access
# include <stdio.h> // perror
# include <fcntl.h> // open
# include <string.h> // strerror
# include <errno.h> 
# include <sys/types.h>
# include <sys/wait.h>

// pipex_utils.c
int open_file(char *filepath, char mode, int *pipefd);
char *find_path(char **command_array, char **env);
char *ft_getenv(char *key, char **env);
void free_array(char **array);

// pipex_errors.c
void file_error(char *filepath, int *pipefd, int flag);
void function_error(char *message, int *pipefd, int flag);
void pipex_error(void);
void cmd_check_error(char *cmd, int fd, int *pipefd);
void close_pipe_ends(int *pipefd);

#endif