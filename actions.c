/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leborges <leborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:12:26 by leborges          #+#    #+#             */
/*   Updated: 2023/04/21 17:22:34 by leborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	t_struct	*args;

	args = philo->args;
	pthread_mutex_lock(&(args->fork[philo->left_f]));
	pthread_mutex_lock(&(args->fork[philo->right_f]));
	eating_print(time_dif(time_ms(), args->time_stamp), PICK, EAT, philo);
	pthread_mutex_lock(&args->check);
	philo->last_meal = time_ms();
	philo->philo_ate += 1;
	pthread_mutex_unlock(&args->check);
	usleep(philo->args->time_eat * 1000);
	pthread_mutex_unlock(&(args->fork[philo->left_f]));
	pthread_mutex_unlock(&(args->fork[philo->right_f]));
}

void	sleep_(t_struct *args, int philo_num)
{
	sleeping_print(time_dif(time_ms(), args->time_stamp),
		SLEEP, args, philo_num);
	usleep(args->time_sleep * 1000);
}

void	monitoring(t_struct *args)
{
	int	i;

	while (!args->all_ate && !args->died)
	{
		i = -1;
		while (++i < args->num_of_philos)
		{
			pthread_mutex_lock(&args->check);
			if (time_dif(time_ms(), args->philo[i].last_meal) > args->time_die)
			{
				pthread_mutex_lock(&args->check_died);
				args->died = 1;
				pthread_mutex_unlock(&args->check_died);
				die_print(time_dif(time_ms(), args->time_stamp),
					DIE, args->philo);
				pthread_mutex_unlock(&args->check);
				return ;
			}
			monitoring_2(args, i);
			pthread_mutex_unlock(&args->check);
		}
	}
}

void	monitoring_2(t_struct *args, int i)
{
	if (args->philo[i].philo_ate == args->must_eat && args->philo[i].done == 0)
	{
		args->philo[i].done++;
		args->yumyum++;
	}
	if (args->yumyum == args->num_of_philos)
		args->all_ate = 1;
}
