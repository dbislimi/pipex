/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:15:45 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/06 18:53:00 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	change_fd(char *file, int fd, char **av)
{
	int	newfd;

	if (fd == 0)
		newfd = open(file, O_RDONLY);
	else if (fd == 1 && ft_strcmp(av[1], "here_doc") == 0)
		newfd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
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

void	ft_close(int i, t_fds p, t_main m)
{
	if (i % 2 == 1)
	{
		if (i != 1)
			close(p.pipe2[0]);
		close(p.pipe1[1]);
	}
	else if (i % 2 == 0)
	{
		if (i != m.ac - 3)
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

void	command_not_found(char *cmd, t_main m, int i)
{
	if (i == 1 && open(m.av[1], O_RDONLY) == -1)
		ft_printf("Error: %s: %s\n", strerror(errno), m.av[1]);
	else if (i == m.ac - 3)
		open(m.av[m.ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	ft_printf("Error: command not found: %s\n", cmd);
}
