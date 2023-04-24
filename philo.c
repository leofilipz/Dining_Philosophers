/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leborges <leborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:18:08 by leborges          #+#    #+#             */
/*   Updated: 2023/04/21 15:36:21 by leborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_struct	args;

	if ((ac == 5 || ac == 6) && confirm_args(av) == 1
		&& create_args(&args, av) == 1)
	{
		printf("The Dining Philosophers Program Has Started\n");
		start(&args);
		if (args.all_ate == 1)
			printf(SATISFIED);
	}	
	else
		print_requirements();
}
