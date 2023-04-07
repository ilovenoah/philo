/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoeat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:21:46 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/07 10:55:21 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	odd_eat(t_philo *philo)
{
	usleep(10);
	pthread_mutex_lock(&philo->env->forks[philo->left_fork]);
	printf("%zu %zu has taken a fork\n", get_time() - philo->env->start_time, philo->id + 1);
	pthread_mutex_lock(&philo->env->forks[philo->right_fork]);
	printf("%zu %zu has taken a fork\n", get_time() - philo->env->start_time, philo->id + 1);
	printf("%zu %zu is eating\n", get_time() - philo->env->start_time, philo->id + 1);
	philo->last_eat = get_time();
	philo->eat_count++;
	usleep(philo->env->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
}

void	even_eat(t_philo *philo)
{
	usleep(10);
	pthread_mutex_lock(&philo->env->forks[philo->right_fork]);
	printf("%zu %zu has taken a fork\n", get_time() - philo->env->start_time, philo->id + 1);
	pthread_mutex_lock(&philo->env->forks[philo->left_fork]);
	printf("%zu %zu has taken a fork\n", get_time() - philo->env->start_time, philo->id + 1);
	printf("%zu %zu is eating\n", get_time() - philo->env->start_time, philo->id + 1);
	philo->last_eat = get_time();
	philo->eat_count++;
	usleep(philo->env->time_to_eat * 1000);
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
