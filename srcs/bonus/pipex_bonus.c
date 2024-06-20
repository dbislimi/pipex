/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:28:59 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/20 20:26:29 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_exit(char *function)
{
	perror(function);
	exit(1);
}

typedef struct	s_main
{
	char	**av;
	int		ac;
}	t_main;

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
	printf("new%d\n", newfd);
	dup2(newfd, fd);
	return (1);
}

void	command1(char **av, int fd0[2], int fd1[2], int i)
{
	char	**command;
	char	*pathname;
	int		pid;

	pid = fork();
	command = ft_split(av[2 + i], ' ');
	pathname = ft_strjoin("/bin/", command[0]);
	if (pid == 0)
	{
		if (i == 0)
		{
			if (change_std(0, av[1]) && dup2(fd0[1], 1) == 1)
			{
				execve(pathname, command, NULL);
			}	
		}
		if (i != 0)
			if (dup2(fd1[0], 0) == 0 && dup2(fd0[1], 1) == 1)
				execve(pathname, command, NULL);
	}
	else if (pid != 0)
		wait(NULL);
	free_tab(command);
	free(pathname);
	// close(fd1);
	// close(fd0);
	if (pid == 0)
		exit(1);
}

void	command2(t_main main, int fd0[2], int fd1[2], int i, int *status)
{
	char	**command;
	char	*pathname;
	int		pid;

	pid = fork();
	command = ft_split(main.av[3 + i], ' ');
	pathname = ft_strjoin("/bin/", command[0]);
	if (pid == 0)
	{
		if (i == main.ac - 4)
			if (change_std(1, main.av[main.ac - 1]) && dup2(fd0[0] ,0) == 0)
				execve(pathname, command, NULL);
		if (i != main.ac - 4)
		{
			printf("hellp\n");
			printf("%d\n", fd0[0]);
			printf("%s", get_next_line(0));
			if (dup2(fd0[0], 0) == 0 && dup2(fd1[1], 1) == 1)
				execve(pathname, command, NULL);
		}
	}
	free_tab(command);
	free(pathname);
	// close(fd0);
	// close(fd1);
	if (pid != 0)
		if (waitpid(pid, status, 0) == -1)
			ft_exit("waitpid");
	if (pid == 0)
		exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_main	main;
	int	fd0[2];
	int	fd1[2];
	int	nbofcommands;
	int	i;
	int	status;

	i = 0;
	main.ac = ac;
	main.av = av;
	nbofcommands = ac - 3;
	pipe(fd0);
	pipe(fd1);
	while (i < nbofcommands)
	{
		// pipe(fd0);
		// if (i == 0 || i % 2 == 0)
		// 	pipe(fd1);
		printf("i : %d\n", i);
		command1(av, fd0, fd1, i);
		printf("fd0 : %s", get_next_line(fd0[0]));
		command2(main, fd0, fd1, i++, &status);
		printf("fd1 : %s", get_next_line(fd1[0]));
	}
}
