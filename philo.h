/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leborges <leborges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:18:11 by leborges          #+#    #+#             */
/*   Updated: 2023/04/21 17:19:41 by leborges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define SATISFIED "All philosophers are satisfied 😌 \n"
# define PICK "has taken a fork 🥢"
# define EAT "is eating 🍜"
# define SLEEP "is sleeping 😴"
# define THINK "is thinking 🤔"
# define DIE "died 💀"

# define LINE "	|-------------------------------------------\
--------------------------------|\n"
# define LINE2 "	|                             ERROR \
 WRONG INPUT:                           |\n"
# define LINE3 "	|                                            \
                               |\n"
# define LINE4 "	|  -The program only accpets numbers as argume\
nts;                          |\n"
# define LINE5 "	|  -The number of philosophers should be greate\
r than 0 and less than 200;  |\n"
# define LINE6 "	|  -Any argument related to time should be grea\
ter than 60;                 |\n"
# define LINE7 "	|-----------------------------------------------\
----------------------------|\n"

typedef struct s_struct {
	int				num_of_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				all_ate;
	int				died;
	int				yumyum;
	suseconds_t		time_stamp;
	pthread_t		monitor;
	pthread_mutex_t	fork[250];
	pthread_mutex_t	check;
	pthread_mutex_t	check_died_full;
	pthread_mutex_t	check_died;
	pthread_mutex_t	print;
	struct s_philo	*philo;
}				t_struct;

typedef struct s_philo {
	t_struct		*args;
	pthread_t		thread;
	suseconds_t		last_meal;
	int				done;
	int				philo_num;
	int				philo_ate;
	int				left_f;
	int				right_f;
}				t_philo;

// Utils
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
// Confirming
int			confirm_args(char **av);
void		print_requirements(void);
// Creating
int			create_args(t_struct *args, char **av);
void		create_philo(t_struct *args);
suseconds_t	time_ms(void);
suseconds_t	time_dif(int act, int prev);
// Threads
void		start(t_struct *args);
void		*routine(void *philosopher);
int			create_mutex(t_struct *args);
// Actions
void		monitoring(t_struct *args);
void		monitoring_2(t_struct *args, int i);
void		eat(t_philo *philo);
void		sleep_(t_struct *args, int philo_num);
// Prints
void		eating_print(suseconds_t time, char *pick,
				char *eat, t_philo *philo);
void		sleeping_print(suseconds_t time, char *sleep,
				t_struct *args, int philo_num);
void		thinking_print(suseconds_t time, char *think, t_philo *philo);
void		die_print(suseconds_t time, char *die, t_philo *philo);
void		gone(t_struct *args);

#endif