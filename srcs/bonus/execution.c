/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:13:07 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/06 17:30:44 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	last_command(int i, t_command cmd, t_fds p, t_main m)
{
	if (i % 2 == 1)
		dup2(p.pipe2[0], 0);
	else if (i % 2 == 0)
		dup2(p.pipe1[0], 0);
	ft_close(i, p, m);
	execve(cmd.pathname, cmd.cmd, m.envp);
	return (0);
}

static void	first_command(t_main m, t_command cmd, t_fds p)
{
	if (!change_fd(m.av[1], 0, m.av))
		return ;
	dup2(p.pipe1[1], 1);
	execve(cmd.pathname, cmd.cmd, m.envp);
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
	else if (i == m.ac - 3)
	{
		if (change_fd(m.av[m.ac - 1], 1, m.av))
			last_command(i, cmd, p, m);
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
	execve(cmd.pathname, cmd.cmd, m.envp);
}
