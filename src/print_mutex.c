/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:44:19 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/11 15:17:34 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	chenge_deadflag(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->dead);
	philo->env->dead_flag = true;
	pthread_mutex_unlock(&philo->env->dead);
}

void	chenge_fullflag(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->full);
	philo->env->must_eat_flag = true;
	pthread_mutex_unlock(&philo->env->full);
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
