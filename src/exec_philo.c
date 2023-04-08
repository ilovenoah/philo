/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:06:55 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/08 20:05:27 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_philo_forks(t_philo *philo)
{
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// if ( philo->eat_count == philo->env->must_eat)
		// 	break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	init_philo(t_env *env, t_philo *philo, size_t i)
{
	philo->id = i;
	philo->env = env;
	philo->eat_count = 0;
	philo->error = false;
	set_philo_forks(philo);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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
	if (!th || !philo)
	{
		env->error = true;
		return ;
	}
	while (i < env->philo_num)
	{
		init_philo(env, &philo[i], i);
		i++;
	}
	i = 0;
	printf("philo_num: %zu\n", env->philo_num);
	while (i < env->philo_num)
	{
		pthread_create(&th[i], NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < env->philo_num)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}
