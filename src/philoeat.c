/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoeat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:21:46 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/09 22:55:39 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	lock_full_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->eat);
	philo->env->full_philo++;
	pthread_mutex_unlock(&philo->env->eat);
}

void	odd_eat(t_philo *philo)
{
	time_t	start;

	pthread_mutex_lock(&philo->env->forks[philo->left_fork]);
	print_mutex(philo, "has taken a fork");
	pthread_mutex_lock(&philo->env->forks[philo->right_fork]);
	print_mutex(philo, "has taken a fork");
	philo->last_eat = get_time();
	philo->eat_count++;
	if (philo->eat_count == philo->env->must_eat)
		lock_full_philo(philo);
	usleep(10);
	print_mutex(philo, "is eating");
	start = get_time();
	while (get_time() - philo->last_eat < philo->env->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
}

void	even_eat(t_philo *philo)
{
	time_t	start;

	pthread_mutex_lock(&philo->env->forks[philo->right_fork]);
	print_mutex(philo, "has taken a fork");
	pthread_mutex_lock(&philo->env->forks[philo->left_fork]);
	print_mutex(philo, "has taken a fork");
	philo->last_eat = get_time();
	philo->eat_count++;
	if (philo->eat_count == philo->env->must_eat)
		lock_full_philo(philo);
	usleep(10);
	print_mutex(philo, "is eating");
	start = get_time();
	while (get_time() - start < philo->env->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
		odd_eat(philo);
	else
		even_eat(philo);
}
