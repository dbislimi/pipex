/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:08:54 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/18 19:49:20 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	change_std(int fd, char *file)
{
	int	newFd;

	newFd = open(file, O_RDONLY);
	if (newFd == -1)
		perror("Error\n");
	dup2(newFd, fd);
}
void	cmd1(char *pathname, char **cmd, char *file, int fd)
{
	change_std(0, file);
	dup2(1, fd);
	close(fd);
	execve(pathname, cmd, NULL);
}

void	cmd2(char *pathname, char **cmd, int *fd)
{
	dup2(0, fd[0]);
	dup2(1, fd[1]);
	close(fd[1]);
	close(fd[0]);
	execve(pathname, cmd, NULL);
}

int main(int ac, char **av)
{
	(void)ac;
	char	*pathname;
	char	**cmd;
	char	*result;
	int	fd[2];
	int	pid[2];
	
	if (pipe(fd) == -1)
		perror("Error\n");
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(fd[0]);
		cmd = ft_split(av[2], ' ');
		pathname = ft_strjoin("/bin/", cmd[0]);
		cmd1(pathname, cmd, av[1], fd[1]);
		free(pathname);
		free_tab(cmd);
	}
	else
	{
		printf("%s", get_next_line(fd[0]));
		pid[1] = fork();
		if (pid[1] == 0)
		{
			cmd = ft_split(av[3], ' ');
			pathname = ft_strjoin("/bin/", cmd[0]);
			cmd2(pathname, cmd, fd);
		}
		else
		{
			close(fd[1]);
			printf("kesako\n");
			result = get_next_line(fd[0]);
			while (result)
			{
				ft_printf("result :%s", result);
				free(result);
				result = get_next_line(fd[0]);	
			}
			close(fd[0]);
		}
	}
	return (0);
}
