/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_more_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:49:53 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/17 12:52:15 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup2_error(int fd1, int fd2, char *msg)
{
	if (fd1 != NULL)
		close(fd1);
	if (fd2 != NULL)
		close(fd2);
	function_error(msg, NULL, 0);
}
