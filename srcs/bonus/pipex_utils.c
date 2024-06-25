/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:15:45 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/25 18:46:39 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	change_fd(char *file, int fd)
{
	int	newfd;

	if (fd == 0)
		newfd = open(file, O_RDONLY);
	else
		newfd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (newfd == -1)
	{
		ft_printf("Error: %s: %s\n", strerror(errno), file);
		return (0);
	}
	dup2(newfd, fd);
	close(newfd);
	return (1);
}

void	ft_close(int i, t_fds p)
{
	if (i % 2 == 1)
	{
		if (i != 1)
			close(p.pipe2[0]);
		close(p.pipe1[1]);
	}
	else if (i % 2 == 0)
	{
		close(p.pipe2[1]);
		close(p.pipe1[0]);
	}
}

void	close_all(t_fds p)
{
	close(p.pipe1[0]);
	close(p.pipe1[1]);
	close(p.pipe2[0]);
	close(p.pipe2[1]);
}
