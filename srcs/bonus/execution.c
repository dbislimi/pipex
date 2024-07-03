/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:13:07 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/03 19:03:34 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	last_command(int i, t_command cmd, t_fds p)
{
	if (i % 2 == 1)
		dup2(p.pipe2[0], 0);
	else if (i % 2 == 0)
		dup2(p.pipe1[0], 0);
	execve(cmd.pathname, cmd.cmd, NULL);
	return (0);
}

static void	first_command(t_main m, t_command cmd, t_fds p)
{
	if (!change_fd(m.av[1], 0, m.av))
		return ;
	dup2(p.pipe1[1], 1);
	execve(cmd.pathname, cmd.cmd, NULL);
}

void	execute(int i, t_main m, t_command cmd, t_fds p)
{
	if (i == 1)
	{
		first_command(m, cmd, p);
		close(p.pipe1[0]);
		close(p.pipe1[1]);
		return ;
	}
	else if (i == m.ac - 3 && change_fd(m.av[m.ac - 1], 1, m.av))
	{
		last_command(i, cmd, p);
		return ;
	}
	if (i % 2 == 1)
	{
		dup2(p.pipe2[0], 0);
		dup2(p.pipe1[1], 1);
	}
	else if (i % 2 == 0)
	{
		dup2(p.pipe1[0], 0);
		dup2(p.pipe2[1], 1);
	}
	close_all(p);
	execve(cmd.pathname, cmd.cmd, NULL);
}
