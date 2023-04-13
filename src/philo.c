/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:11:36 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/13 21:59:05 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex_forks(t_env *env)
{
	size_t	i;

	i = 0;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->philo_num);
	if (!env->forks)
		return (-1);
	while (i < env->philo_num)
	{
		pthread_mutex_init(&env->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&env->full, NULL);
	pthread_mutex_init(&env->print, NULL);
	pthread_mutex_init(&env->eat, NULL);
	pthread_mutex_init(&env->dead, NULL);
	return (0);
}

static void	destroy_mutex_and_free(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->philo_num)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->full);
	pthread_mutex_destroy(&env->print);
	pthread_mutex_destroy(&env->eat);
	pthread_mutex_destroy(&env->dead);
	free(env->forks);
}

void	philomutex_destroy_and_free(t_env *env, t_philo *philo, pthread_t *th)
{
	size_t	i;

	i = 0;
	while (i < env->philo_num)
	{
		pthread_mutex_destroy(&philo[i].l_eat);
		i++;
	}
	free(philo);
	free(th);
}

void	create_philo(t_env *env)
{
	t_philo		*philo;
	pthread_t	*th;
	time_t		start;

	start = get_time();
	env->start_time = start;
	philo = malloc(sizeof(t_philo) * env->philo_num);
	if (errno == ENOMEM)
		return ;
	th = malloc(sizeof(pthread_t) * env->philo_num);
	if (errno == ENOMEM)
	{
		free(philo);
		return ;
	}
	philo_exec(env, philo, th);
	philomutex_destroy_and_free(env, philo, th);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (error_check(argc, argv))
		return (-1);
	if (set_env_data(&env, argv) == -1)
		return (-1);
	if (init_mutex_forks(&env) == -1)
		return (-1);
	create_philo(&env);
	destroy_mutex_and_free(&env);
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo");
// }