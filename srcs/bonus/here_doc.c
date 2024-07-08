/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:20:58 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/08 20:30:48 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	here_doc(int fd[2], char *limiter, int *i)
{
	char	*line;
	char	*lim;

	pipe(fd);
	lim = ft_strjoin(limiter, "\n");
	write(1, ">", 1);
	line = get_next_line(0);
	while (ft_strcmp(lim, line))
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		write(1, ">", 1);
		line = get_next_line(0);
	}
	free(lim);
	free(line);
	close(fd[1]);
	*i = 1;
}
