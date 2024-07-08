/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:13:55 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/08 20:21:16 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/ft_printf.h"
# include <errno.h>
# include <sys/wait.h>

// MANDATORY

typedef struct s_main
{
	char	**av;
	int		ac;
	char	**envp;
	int		heredoc_flag;
}	t_main;

typedef struct s_command
{
	char	**cmd;
	char	*pathname;
}	t_command;

int		change_std(int fd, char *file);
char	*find_path(char *cmd, char **envp);
char	*check_path(char *cmd, char **envp);
void	execution(int i, t_main m, t_command cmd, int fd[2]);
void	not_a_command(char *cmd, t_main m, int i);

// BONUS


typedef struct s_fds
{
	int	pipe1[2];
	int	pipe2[2];
}	t_fds;


char	*find_path(char *cmd, char **envp);
void	execute(int i, t_main m, t_command cmd, t_fds p);
int		change_fd(char *file, int fd, char **av);
void	close_all(t_fds p);
void	ft_close(int i, t_fds p, t_main m);
void	here_doc(int fd[2], char *limiter, int *i);
void	command_not_found(char *cmd, t_main m, int i);

#endif