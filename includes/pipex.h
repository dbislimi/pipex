/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:13:55 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/21 16:10:13 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/ft_printf.h"
# include <errno.h>
# include <sys/wait.h>

// BONUS

typedef struct	s_command
{
	char	**cmd;
	char	*pathname;
	int		nb_of_cmds;
}	t_command;

typedef struct	s_fds
{
	int	pipe1[2];
	int	pipe2[2];
	int	fdfile1;
	int fdfile2;
}	t_fds;

typedef struct	s_main
{
	char	**av;
	int		ac;
}	t_main;

void	execute(int i, t_main m, t_command cmd, t_fds p);
int	get_fd(char *file, int i);

#endif