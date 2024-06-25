/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:08:54 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/21 18:23:08 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_exit(char *function)
{
	perror(function);
	exit(1);
}
// int	ft_close(int nbofarg, ...)
// {
// 	va_list	arg;

// 	va_start(arg, nbofarg);
// 	while (nbofarg--)
// 		close(va_arg(arg, int));
// 	va_end(arg);
// 	return (1);
// }

int	change_std(int fd, char *file)
{
	int	newfd;

	if (fd == 0)
		newfd = open(file, O_RDONLY);
	else
		newfd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (newfd == -1)
	{
		ft_printf("Error: %s: %s\n", strerror(errno), file);
		return (0);
	}
	dup2(newfd, fd);
	close(newfd);
	return (1);
}

void	command1(char **av, int fd[2])
{
	char	**command;
	char	*pathname;
	int		pid;

	pid = fork();
	command = ft_split(av[2], ' ');
	pathname = ft_strjoin("/bin/", command[0]);
	if (pid == 0)
	{
		close(fd[0]);
		if (change_std(0, av[1]))
		{
			dup2(fd[1], 1);
			close(fd[1]);
			execve(pathname, command, NULL);
		}
	}
	free_tab(command);
	free(pathname);
	close(fd[1]);
	if (pid == 0)
		exit(1);
}

void	command2(char **av, int fd[2], int *status)
{
	char	**command;
	char	*pathname;
	int		pid;

	pid = fork();
	command = ft_split(av[3], ' ');
	pathname = ft_strjoin("/bin/", command[0]);
	if (pid == 0 && change_std(1, av[4]))
	{
		dup2(fd[0], 0);
		close(fd[0]);
		execve(pathname, command, NULL);
	}
	free_tab(command);
	free(pathname);
	close(fd[0]);
	if (pid != 0)
		if (waitpid(pid, status, 0) == -1)
			ft_exit("waitpid");
	if (pid == 0)
		exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	int		commands_pipe[2];
	int		status;

	(void)ac;
	if (pipe(commands_pipe) == -1)
		return (1);
	command1(av, commands_pipe);
	command2(av, commands_pipe, &status);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (1);
	return (0);
}
