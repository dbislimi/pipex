/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:13:24 by dbislimi          #+#    #+#             */
/*   Updated: 2024/06/17 20:14:33 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/ft_printf.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		ft_printf("(null)\n");
	while (tab[i])
		ft_printf("%s\n", tab[i++]);
	ft_printf("\n");
}
