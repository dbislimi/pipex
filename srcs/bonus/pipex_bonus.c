/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:28:59 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/06 18:52:46 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	*path_with_cmd;
	char	**paths;

	i = -1;
	while (ft_strncmp(envp[++i], "PATH", 4) != 0)
		;
	paths = ft_split(envp[i], ':');
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path_with_cmd = ft_strjoin(path, cmd);
		if (access(path_with_cmd, F_OK) == 0)
		{
			free_tab(paths);
			free(path);
			return (path_with_cmd);
		}
		free(path);
		free(path_with_cmd);
	}
	free_tab(paths);
	return (NULL);
}

void	command(t_main m, t_fds p, int i)
{
	t_command	cmd;
	int			pid;

	cmd.cmd = ft_split(m.av[1 + i], ' ');
	cmd.pathname = find_path(cmd.cmd[0], m.envp);
	pid = fork();
	if (cmd.pathname == NULL && pid != 0)
		command_not_found(cmd.cmd[0], m, i);
	else if (cmd.pathname)
	{
		if (pid == 0)
			execute(i, m, cmd, p);
		else if (i == m.ac - 3 && pid != 0)
			wait(NULL);
	}
	free_tab(cmd.cmd);
	free(cmd.pathname);
	ft_close(i, p, m);
	if (pid == 0)
		exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_main	main;
	t_fds	p;
	int		i;

	i = 0;
	main.ac = ac;
	main.av = av;
	main.envp = envp;
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		here_doc(p.pipe1, ac - 5, av[2]);
		i = 1;
	}
	while (++i <= ac - 3)
	{
		if (i % 2 == 1)
			pipe(p.pipe1);
		else if (i != ac - 3 && i % 2 == 0)
			pipe(p.pipe2);
		command(main, p, i);
	}
	if (i % 2 == 0)
		close(p.pipe1[0]);
}
