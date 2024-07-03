/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:28:59 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/03 19:01:07 by dbislimi         ###   ########.fr       */
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
void	here_doc_margin(int nb_of_pipes)
{
	while (nb_of_pipes--)
		write(1, "pipe ", 6);
	write(1, "heredoc>", 8);
}

void	here_doc(int fd[2], int nb_of_pipes, char *limiter)
{
	char	*line;
	int	i;

	pipe(fd);
	i = nb_of_pipes;
	here_doc_margin(nb_of_pipes);
	line = get_next_line(0);
	while (ft_strncmp(line, limiter, ft_strlen(line) - 1))
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		here_doc_margin(nb_of_pipes);
		line = get_next_line(0);
	}
	close(fd[1]);
}

int	main(int ac, char **av)
{
	t_main	main;
	t_fds	p;
	int		i;

	i = 0;
	main.ac = ac;
	main.av = av;
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
	ft_close(i, p);
}
