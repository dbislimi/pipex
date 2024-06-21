/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:13:07 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/21 16:13:26 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	last_command(int i, t_command cmd, t_fds p)
{
	if (i % 2 == 0)
		dup2(p.pipe2[0], 0);
	else if (i % 2 == 1)
		dup2(p.pipe1[0], 0);
	dup2(p.fdfile2, 1);
	execve(cmd.pathname, cmd.cmd, NULL);
}

void	execute(int i, t_main m, t_command cmd, t_fds p)
{
	if (i == 0)
	{
		dup2(p.fdfile1, 0);
		dup2(p.pipe1[1], 1);
	}
	else if (i == m.ac - 4)
		last_command(i, cmd, p);
	else if (i % 2 == 0)
	{
		dup2(p.pipe2[0], 0);
		dup2(p.pipe1[1], 1);
	}
	else if (i % 2 == 1)
	{
		dup2(p.pipe1[0], 0);
		dup2(p.pipe2[1], 1);
	}
	execve(cmd.pathname, cmd.cmd, NULL);
}
