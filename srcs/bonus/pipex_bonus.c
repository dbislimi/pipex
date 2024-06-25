/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:28:59 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/25 18:47:29 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	command(t_main m, t_fds p, int i)
{
	t_command	cmd;
	int			pid;

	pid = fork();
	cmd.cmd = ft_split(m.av[1 + i], ' ');
	cmd.pathname = ft_strjoin("/bin/", cmd.cmd[0]);
	if (pid == 0)
		execute(i, m, cmd, p);
	else if (i == m.ac - 3 && pid != 0)
		wait(NULL);
	free_tab(cmd.cmd);
	free(cmd.pathname);
	if (pid == 0)
		exit(1);
	ft_close(i, p);
}

int	main(int ac, char **av)
{
	t_main	main;
	t_fds	p;
	int		nbofcommands;
	int		i;

	i = 0;
	main.ac = ac;
	main.av = av;
	nbofcommands = ac - 3;
	while (++i <= nbofcommands)
	{
		if (i % 2 == 1)
			pipe(p.pipe1);
		else if (i != ac - 3 && i % 2 == 0)
			pipe(p.pipe2);
		command(main, p, i);
	}
	ft_close(i, p);
}
