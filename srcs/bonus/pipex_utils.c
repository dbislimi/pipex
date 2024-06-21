/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:15:45 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/21 16:01:43 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	get_fd(char *file, int i)
{
	int	fd;

	if (i == 0)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		ft_printf("Error: %s: %s\n", strerror(errno), file);
		return (0);
	}
	return (fd);
}
