/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leborges <leborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:27:32 by leborges          #+#    #+#             */
/*   Updated: 2023/04/21 13:58:36 by leborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutex(t_struct *args)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philos)
		if (pthread_mutex_init(&args->fork[i], NULL))
			return (0);
	if (pthread_mutex_init(&args->check, NULL))
		return (0);
	if (pthread_mutex_init(&args->check_died, NULL))
		return (0);
	if (pthread_mutex_init(&args->print, NULL))
		return (0);
	if (pthread_mutex_init(&args->check_died_full, NULL))
		return (0);
	return (1);
}

void	start(t_struct *args)
{
	int		i;
	t_philo	*philo;

	philo = args->philo;
	i = -1;
	args->time_stamp = time_ms();
	while (++i < args->num_of_philos)
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
	monitoring(args);
	gone(args);
}

void	*routine(void *philosopher)
{
	t_philo		*philo;
	t_struct	*args;

	philo = (t_philo *)philosopher;
	args = philo->args;
	while (1)
	{
		pthread_mutex_lock(&args->check_died);
		if (!args->died && !args->all_ate
			&& args->num_of_philos > 1 && philo->done == 0)
		{
			pthread_mutex_unlock(&args->check_died);
			eat(philo);
			sleep_(args, philo->philo_num);
			thinking_print(time_dif(time_ms(), args->time_stamp), THINK, philo);
		}
		else
		{
			pthread_mutex_unlock(&args->check_died);
			break ;
		}
	}
	return (NULL);
}
