/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:15:26 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/08 19:17:08 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	command(t_main m, int fd[2], int *status, int i)
{
	t_command	cmd;
	int			pid;

	cmd.cmd = ft_split(m.av[1 + i], ' ');
	cmd.pathname = check_path(cmd.cmd[0], m.envp);
	pid = fork();
	if (cmd.pathname == NULL && pid != 0)
		not_a_command(cmd.cmd[0], m, i);
	if (pid == 0 && cmd.pathname != NULL)
		execution(i, m, cmd, fd);
	else if (i != 1 && pid != 0)
		waitpid(pid, status, 0);
	free_tab(cmd.cmd);
	free(cmd.pathname);
	if (i == 1)
		close(fd[1]);
	else
		close(fd[0]);
	if (pid == 0)
		exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_main	main;
	int		status;
	int		fd[2];

	status = 0;
	if (ac != 5)
	{
		if (ac > 5)
			write(2, "Too many arguments\n", 20);
		else if (ac < 5)
			write(2, "Too few arguments\n", 19);
		return (1);
	}
	if (pipe(fd) == -1)
		return (1);
	main.ac = ac;
	main.av = av;
	main.envp = envp;
	command(main, fd, NULL, 1);
	command(main, fd, &status, 2);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) != 0)
			return (1);
	return (0);
}
