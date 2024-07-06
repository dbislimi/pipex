/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:20:58 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/06 18:53:47 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	here_doc_margin(int nb_of_pipes)
{
	while (nb_of_pipes--)
		write(1, "pipe ", 6);
	write(1, "heredoc>", 8);
}

void	here_doc(int fd[2], int nb_of_pipes, char *limiter)
{
	char	*line;
	char	*lim;

	pipe(fd);
	lim = ft_strjoin(limiter, "\n");
	here_doc_margin(nb_of_pipes);
	line = get_next_line(0);
	while (ft_strcmp(lim, line))
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		here_doc_margin(nb_of_pipes);
		line = get_next_line(0);
	}
	free(lim);
	free(line);
	close(fd[1]);
}
