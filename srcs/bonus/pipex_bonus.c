/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:28:59 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/08 21:50:15 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	command(t_main m, t_fds p, int *status, int i)
{
	t_command	cmd;
	int			pid;

	cmd.cmd = ft_split(m.av[1 + i], ' ');
	if (access(cmd.cmd[0], F_OK) == 0)
		cmd.pathname = ft_strdup(cmd.cmd[0]);
	else
		cmd.pathname = find_path(cmd.cmd[0], m.envp);
	pid = fork();
	if (cmd.pathname == NULL && pid != 0)
		command_not_found(cmd.cmd[0], m, i);
	if (pid == 0 && cmd.pathname)
		execute(i, m, cmd, p);
	else if (pid != 0 && i == m.ac - 3)
		waitpid(pid, status, 0);
	free_tab(cmd.cmd);
	free(cmd.pathname);
	ft_close(i, p, m);
	if (pid == 0)
		exit(EXIT_FAILURE);
}

static void	pipex(t_fds p, t_main m, int *status, int i)
{
	while (++i <= m.ac - 3)
	{
		if (i % 2 == 1 && i != 1)
			pipe(p.pipe1);
		else if (i != m.ac - 3 && i % 2 == 0 && i != 2)
			pipe(p.pipe2);
		command(m, p, status, i);
	}
	if (i % 2 == 0)
		close(p.pipe1[0]);
}

static int	pipes_init(t_fds *p)
{
	if (pipe(p->pipe1) == -1)
		return (0);
	if (pipe(p->pipe2) == -1)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_main	main;
	t_fds	p;
	int		status;
	int		i;

	i = 0;
	if (!pipes_init(&p))
		return (1);
	main.ac = ac;
	main.av = av;
	main.envp = envp;
	if (ac < 5 && write(1, "Too few arguments\n", 19))
		return (1);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6 && write(1, "Too few arguments\n", 19))
			return (1);
		here_doc(p.pipe1, av[2], &i);
	}
	pipex(p, main, &status, i);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) != 0)
			return (1);
	return (0);
}
