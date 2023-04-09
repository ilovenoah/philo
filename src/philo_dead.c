/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:44:36 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/09 23:02:27 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// bool	check_eat(t_philo *philo)
// {
// 	size_t	i;

// 	i = 0;
// 	if (philo->env->must_eat == 0)
// 		return (false);
// 	while (i < philo->env->philo_num)
// 	{
// 		if (philo[i].eat_count < philo->env->must_eat)
// 			return (false);
// 		i++;
// 	}
// 	pthread_mutex_lock(&philo->env->eat);
// 	philo->env->must_eat_flag = true;
// 	pthread_mutex_unlock(&philo->env->eat);
// 	return (true);
// }

bool	checkdie(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->env->philo_num)
	{
		if (get_time() - philo[i].last_eat > philo->env->time_to_die)
		{
			pthread_mutex_lock(&philo->env->dead);
			usleep(10);
			print_mutex(&philo[i], "died");
			pthread_mutex_unlock(&philo->env->dead);
			return (true);
		}
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
