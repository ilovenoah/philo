/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:44:19 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/13 21:28:52 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_sleep(t_philo *philo)
{
	time_t	start;

	print_mutex(philo, "is sleeping");
	start = get_time();
	while (get_time() - start < philo->env->time_to_sleep)
		usleep(100);
}

void	chenge_fullflag(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->full);
	philo->env->must_eat_flag = true;
	pthread_mutex_unlock(&philo->env->full);
}

void	chenge_deadflag(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->dead);
	philo->env->dead_flag = true;
	pthread_mutex_unlock(&philo->env->dead);
}

void	print_mutex(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->env->print);
	if (checkflag(philo))
	{
		pthread_mutex_unlock(&philo->env->print);
		return ;
	}
	if (ft_strcmp(str, "died") == 0)
		chenge_deadflag(philo);
	pthread_mutex_lock(&philo->env->eat);
	if (ft_strcmp(str, "is eating") == 0 \
		&& philo->env->full_philo == philo->env->philo_num)
		chenge_fullflag(philo);
	pthread_mutex_unlock(&philo->env->eat);
	printf("%zu %zu %s\n", \
		get_time() - philo->env->start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->env->print);
}
