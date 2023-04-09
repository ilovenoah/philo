/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:06:55 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/09 22:54:55 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->env->dead_flag == true || philo->env->must_eat_flag == true)
			break ;
		philo_eat(philo);
		if (philo->env->dead_flag == true || philo->env->must_eat_flag == true)
			break ;
		philo_sleep(philo);
		if (philo->env->dead_flag == true || philo->env->must_eat_flag == true)
			break ;
		print_mutex(philo, "is thinking");
		if (philo->env->dead_flag == true || philo->env->must_eat_flag == true)
			break ;
	}
	return (NULL);
}

void	init_philo(t_env *env, t_philo *philo, size_t i)
{
	philo->id = i;
	philo->env = env;
	philo->eat_count = 0;
	philo->error = false;
	philo->last_eat = get_time();
	if (philo->id == 0)
	{
		philo->left_fork = philo->env->philo_num - 1;
		philo->right_fork = philo->id;
	}
	else
	{
		philo->left_fork = philo->id - 1;
		philo->right_fork = philo->id;
	}
}

void	philo_exec(t_env *env, t_philo *philo, pthread_t *th)
{
	size_t	i;

	i = 0;
	while (i < env->philo_num)
	{
		init_philo(env, &philo[i], i);
		i++;
	}
	i = 0;
	while (i < env->philo_num)
	{
		pthread_create(&th[i], NULL, philo_routine, &philo[i]);
		i++;
	}
	philo_dead(philo);
	i = 0;
	while (i < env->philo_num)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}

void	create_philo(t_env *env)
{
	size_t		i;
	t_philo		*philo;
	pthread_t	*th;
	time_t		start;

	i = 0;
	start = get_time();
	env->start_time = start;
	philo = malloc(sizeof(t_philo) * env->philo_num);
	th = malloc(sizeof(pthread_t) * env->philo_num);
	if (errno == ENOMEM)
	{
		env->error = true;
		return ;
	}
	philo_exec(env, philo, th);
	free(philo);
	free(th);
}
