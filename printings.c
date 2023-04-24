/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leborges <leborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:36:25 by leborges          #+#    #+#             */
/*   Updated: 2023/04/21 13:51:34 by leborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_print(suseconds_t time, char *pick, char *eat, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->check_died);
	if (!philo->args->died && !philo->args->all_ate)
	{
		printf("Time %ld | Philo %d %s\nTime %ld | Philo %d %s\n", time,
			philo->philo_num, pick, time, philo->philo_num, pick);
		printf("Time %ld | Philo %d %s\n", time, philo->philo_num, eat);
		pthread_mutex_unlock(&philo->args->check_died);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->check_died);
		return ;
	}
}

void	sleeping_print(suseconds_t time, char *sleep,
	t_struct *args, int philo_num)
{
	pthread_mutex_lock(&args->check);
	if (!args->all_ate)
	{
		pthread_mutex_lock(&args->check_died);
		if (args->died)
		{
			pthread_mutex_unlock(&args->check);
			pthread_mutex_unlock(&args->check_died);
			return ;
		}
		if (!args->died)
		{
			printf("Time %ld | Philo %d %s\n", time, philo_num, sleep);
			pthread_mutex_unlock(&args->check_died);
			pthread_mutex_unlock(&args->check);
		}
	}
	else
	{
		pthread_mutex_unlock(&args->check);
		return ;
	}
}

void	thinking_print(suseconds_t time, char *think, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->check);
	if (!philo->args->all_ate)
	{
		pthread_mutex_lock(&philo->args->check_died);
		if (philo->args->died)
		{
			pthread_mutex_unlock(&philo->args->check);
			pthread_mutex_unlock(&philo->args->check_died);
			return ;
		}
		if (!philo->args->died)
		{
			printf("Time %ld | Philo %d %s\n", time, philo->philo_num, think);
			pthread_mutex_unlock(&philo->args->check_died);
			pthread_mutex_unlock(&philo->args->check);
		}
	}
	else
	{
		pthread_mutex_unlock(&philo->args->check);
		return ;
	}		
}

void	die_print(suseconds_t time, char *die, t_philo *philo)
{
	if (philo->args->died == 1)
		printf("Time %ld | Philo %d %s\n", time, philo->philo_num, die);
}

void	gone(t_struct *args)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philos)
		pthread_join(args->philo[i].thread, NULL);
	i = -1;
	while (++i < args->num_of_philos)
		pthread_mutex_destroy(&(args->fork[i]));
	pthread_mutex_destroy(&(args->check));
	pthread_mutex_destroy(&(args->check_died));
	pthread_mutex_destroy(&(args->print));
	free(args->philo);
}
