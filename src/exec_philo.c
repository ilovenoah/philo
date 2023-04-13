/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:06:55 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/13 20:53:58 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	first_action(t_philo *philo, int *first_flag)
{
	pthread_mutex_lock(&philo->l_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->l_eat);
	print_mutex(philo, "is thinking");
	*first_flag = 1;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		first_flag;

	first_flag = 0;
	philo = (t_philo *)arg;
	if (first_flag == 0)
		first_action(philo, &first_flag);
	if (philo->env->philo_num == 1)
		return (one_philo(philo));
	while (1)
	{
		if (checkflag(philo))
			break ;
		philo_eat(philo);
		if (checkflag(philo))
			break ;
		philo_sleep(philo);
		if (checkflag(philo))
			break ;
		print_mutex(philo, "is thinking");
		if (checkflag(philo))
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
	pthread_mutex_init(&philo->l_eat, NULL);
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

int	pthread_create_x(t_env *env, pthread_t *th, t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < env->philo_num)
	{
		if (pthread_create(&th[i], NULL, philo_routine, &philo[i]) != 0)
		{
			printf("Error: pthread_create failed\n");
			env->error = true;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	philo_exec(t_env *env, t_philo *philo, pthread_t *th)
{
	size_t	i;

	i = 0;
	while (i < env->philo_num)
	{
		init_philo(env, &philo[i], i);
		i++;
	}
	if (pthread_create_x(env, th, philo) == -1)
		return (-1);
	philo_dead(philo);
	i = 0;
	while (i < env->philo_num)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	return (0);
}
