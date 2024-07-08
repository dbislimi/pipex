/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:57:05 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/08 19:20:00 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*check_path(char *cmd, char **envp)
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

void	not_a_command(char *cmd, t_main m, int i)
{
	if (i == 1 && open(m.av[1], O_RDONLY) == -1)
	{
		ft_printf("Error: %s: %s\n", strerror(errno), m.av[1]);
		return ;
	}
	else if (i == 2)
		close(open(m.av[m.ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777));
	ft_printf("Error: command not found: %s\n", cmd);
}
