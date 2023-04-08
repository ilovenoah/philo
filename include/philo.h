/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuokaryou <matsuokaryou@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:31:30 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/07 18:36:34 by matsuokaryo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_env
{
	size_t			philo_num;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	size_t			must_eat;
	time_t			start_time;
	bool			error;
	pthread_mutex_t	*forks;
}	t_env;

typedef struct s_philo
{
	size_t			id;
	size_t			last_eat;
	size_t			eat_count;
	size_t			left_fork;
	size_t			right_fork;
	pthread_t		thread;
	t_env			*env;
	bool			error;
}	t_philo;

bool	ft_isdigit(char c);
size_t	ft_atosize(const char *str, t_env *env);
void	create_philo(t_env *env);
time_t	get_time(void);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);



#endif