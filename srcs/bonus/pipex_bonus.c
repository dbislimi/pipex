/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:28:59 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/21 16:21:23 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_close(int i, int ac, t_fds p)
{
	if (i == 0)
	{
		close(p.fdfile1);
		close(p.pipe1[1]);
	}
	else if (i == ac - 4)
		close(p.fdfile2);
	else if (i % 2 == 0)
	{
		close(p.pipe2[0]);
		close(p.pipe1[1]);
	}
	else if (i % 2 == 1)
	{
		close(p.pipe2[1]);
		close(p.pipe1[0]);
	}
}
void	command1(t_main m, t_fds p, int i)
{
	t_command	cmd;
	int		pid;

	pid = fork();
	cmd.cmd = ft_split(m.av[2 + i], ' ');
	cmd.pathname = ft_strjoin("/bin/", cmd.cmd[0]);
	if (pid == 0)
	{
		execute(i, m, cmd, p);
	}
	else if (pid != 0)
		wait(NULL);
	free_tab(cmd.cmd);
	free(cmd.pathname);
	ft_close(i, m.ac, p);
	if (pid == 0)
		exit(1);
}

// void	command2(t_main m, t_pipes p, int i, int *status)
// {
// 	t_command	cmd;
// 	int		pid;

// 	//(void)fd1[2];
// 	pid = fork();
// 	cmd.cmd = ft_split(m.av[3 + i], ' ');
// 	cmd.pathname = ft_strjoin("/bin/", cmd.cmd[0]);
// 	if (pid == 0)
// 	{
// 		execute(i, m, cmd, p);
// 	}
// 	free_tab(cmd.cmd);
// 	free(cmd.pathname);
// 	if (pid != 0)
// 		if (waitpid(pid, status, 0) == -1)
// 			exit(1);
// 	if (pid == 0)
// 		exit(EXIT_FAILURE);
// }

int	main(int ac, char **av)
{
	t_main	main;
	t_fds	p;
	int	nbofcommands;
	int	i;
	// int	status;

	i = 0;
	main.ac = ac;
	main.av = av;
	nbofcommands = ac - 3;
	pipe(p.pipe1);
	pipe(p.pipe2);
	p.fdfile1 = get_fd(av[1], 0);
	p.fdfile2 = get_fd(av[ac - 1], 1);
	while (i < nbofcommands)
	{
		if (i != 0 && i % 2 == 0)
			pipe(p.pipe1);
		else if (i != ac - 1 && i % 2 == 1)
			pipe(p.pipe2);
		command1(main, p, i++);
	}
}
