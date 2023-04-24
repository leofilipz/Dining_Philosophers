/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leborges <leborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:42:12 by leborges          #+#    #+#             */
/*   Updated: 2023/04/20 14:18:37 by leborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

suseconds_t	time_dif(int act, int prev)
{
	return (act - prev);
}

void	create_philo(t_struct *args)
{
	int	i;

	i = 0;
	args->philo = malloc(sizeof(t_philo) * args->num_of_philos);
	while (i < args->num_of_philos)
	{
		args->philo[i].philo_num = i + 1;
		args->philo[i].philo_ate = 0;
		args->philo[i].done = 0;
		args->philo[i].args = args;
		if (args->num_of_philos > 1 && i != (args->num_of_philos - 1))
		{
			args->philo[i].left_f = i;
			args->philo[i].right_f = i + 1;
		}
		else if (args->num_of_philos > 1 && i == (args->num_of_philos - 1))
		{
			args->philo[i].left_f = 0;
			args->philo[i].right_f = i;
		}
		args->philo[i].last_meal = time_ms();
		i++;
	}
}

int	create_args(t_struct *args, char **av)
{
	args->num_of_philos = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	if (av[5])
		args->must_eat = ft_atoi(av[5]);
	else
		args->must_eat = -1;
	args->all_ate = 0;
	args->died = 0;
	args->yumyum = 0;
	if (!create_mutex(args))
		return (0);
	create_philo(args);
	return (1);
}
