/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:28:59 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/08 19:48:31 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	command(t_main m, t_fds p, int *status, int i)
{
	t_command	cmd;
	int			pid;

	cmd.cmd = ft_split(m.av[1 + i], ' ');
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

int	main(int ac, char **av, char **envp)
{
	t_main	main;
	t_fds	p;
	int		status;
	int		i;

	i = 0;
	main.ac = ac;
	main.av = av;
	main.envp = envp;
	if (ft_strcmp(av[1], "here_doc") == 0)
		here_doc(p.pipe1, ac - 5, av[2], &i);
	while (++i <= ac - 3)
	{
		if (i % 2 == 1)
			pipe(p.pipe1);
		else if (i != ac - 3 && i % 2 == 0)
			pipe(p.pipe2);
		command(main, p, &status, i);
	}
	if (i % 2 == 0)
		close(p.pipe1[0]);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) != 0)
			return (1);
	return (0);
}
