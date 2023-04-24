/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confirm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leborges <leborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:55:09 by leborges          #+#    #+#             */
/*   Updated: 2023/04/21 17:20:15 by leborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	confirm_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	i = 2;
	while (i < 5)
	{
		if (ft_atoi(av[i]) < 60)
			return (0);
		i++;
	}
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[1]) > 200)
		return (0);
	return (1);
}

void	print_requirements(void)
{
	printf("\033[1;33m");
	printf("\n\n");
	printf(LINE);
	printf(LINE2);
	printf(LINE);
	printf(LINE3);
	printf(LINE4);
	printf(LINE3);
	printf(LINE5);
	printf(LINE3);
	printf(LINE6);
	printf(LINE3);
	printf(LINE7);
	printf("\n\n");
	printf("\033[0m");
}
