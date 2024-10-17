/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:38 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/17 14:39:37 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *filepath, char mode)
{
	int	fd;

	fd = 0;
	if (mode == 'R' && access(filepath, R_OK) == -1)
		file_error(filepath, NULL, 0);
	if (mode == 'R')
		fd = open(filepath, O_RDONLY);
	else if (mode == 'W')
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 'A')
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		file_error(filepath, NULL, 0);
	return (fd);
}

char	*find_path(char **command_array, char **env)
{
	char	**all_paths;
	char	*command_path;
	char	*tmp;
	int		i;

	all_paths = ft_split(ft_getenv("PATH", env), ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		command_path = ft_strjoin(tmp, command_array[0]);
		free(tmp);
		if (access(command_path, F_OK | X_OK) == 0)
		{
			free_array(all_paths);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free_array(all_paths);
	return (NULL);
}

char	*ft_getenv(char *key, char **env)
{
	int	i;
	int	key_length;

	i = 0;
	key_length = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_length) == 0
			&& env[i][key_length] == '=')
			return (env[i] + key_length + 1);
		i++;
	}
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	close_pipe_ends(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}
