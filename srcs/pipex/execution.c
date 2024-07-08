/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:20:04 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/08 19:20:22 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	execution(int i, t_main m, t_command cmd, int fd[2])
{
	if (i == 1 && change_std(0, m.av[1]))
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(cmd.pathname, cmd.cmd, m.envp);
	}
	else if (i == 2 && change_std(1, m.av[4]))
	{
		dup2(fd[0], 0);
		close(fd[0]);
		execve(cmd.pathname, cmd.cmd, m.envp);
	}
}
