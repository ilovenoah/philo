/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:44:36 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/10 17:41:19 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->forks[philo->left_fork]);
	print_mutex(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
	return (NULL);
}

bool	checkflag(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->dead);
	pthread_mutex_lock(&philo->env->full);
	if (philo->env->dead_flag == true || philo->env->must_eat_flag == true)
	{
		pthread_mutex_unlock(&philo->env->dead);
		pthread_mutex_unlock(&philo->env->full);
		return (true);
	}
	pthread_mutex_unlock(&philo->env->dead);
	pthread_mutex_unlock(&philo->env->full);
	return (false);
}

bool	checkdie(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->env->philo_num)
	{
		pthread_mutex_lock(&philo[i].l_eat);
		if (get_time() - philo[i].last_eat > philo->env->time_to_die)
		{
			pthread_mutex_unlock(&philo[i].l_eat);
			print_mutex(&philo[i], "died");
			return (true);
		}
		pthread_mutex_unlock(&philo[i].l_eat);
		i++;
	}
	return (false);
}

void	philo_dead(t_philo *philo)
{
	while (1)
	{
		if (checkdie(philo) == true)
			break ;
		usleep(10);
	}
}
