/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:11:36 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/09 15:45:17 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	error_check(int argc, char **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (true);
	}
	while (i < (size_t)argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error: Wrong argument type\n");
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

int	set_env_data(t_env *env, char **argv)
{
	env->philo_num = ft_atosize(argv[1], env);
	env->time_to_die = ft_atosize(argv[2], env);
	env->time_to_eat = ft_atosize(argv[3], env);
	env->time_to_sleep = ft_atosize(argv[4], env);
	if (argv[5])
		env->must_eat = ft_atosize(argv[5], env);
	else
		env->must_eat = 0;
	if (argv[5] && env->must_eat == 0)
	{
		printf("Error: Wrong argument type\n");
		return (-1);
	}
	if (env->error == true)
		return (-1);
	if (env->philo_num == 0 || env->time_to_die == 0
		|| env->time_to_eat == 0 || env->time_to_sleep == 0)
	{
		printf("Error: Wrong argument type\n");
		return (-1);
	}
	return (0);
}

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
	pthread_mutex_init(&env->print, NULL);
	return (0);
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
}
