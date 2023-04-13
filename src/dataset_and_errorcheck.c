/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_and_errorcheck.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:52:25 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/13 21:49:30 by rmatsuok         ###   ########.fr       */
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
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (true);
	}
	while (i < (size_t)argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				ft_putstr_fd("Error: Wrong argument type\n", 2);
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

void	set_philo_and_time(t_env *env, char **argv)
{
	env->th_num = 0;
	env->philo_num = ft_atosize(argv[1], env);
	env->time_to_die = ft_atosize(argv[2], env);
	env->time_to_eat = ft_atosize(argv[3], env);
	env->time_to_sleep = ft_atosize(argv[4], env);
	if (argv[5])
		env->must_eat = ft_atosize(argv[5], env);
	else
		env->must_eat = 0;
}

int	set_env_data(t_env *env, char **argv)
{
	env->dead_flag = false;
	env->must_eat_flag = false;
	env->error = false;
	env->full_philo = 0;
	set_philo_and_time(env, argv);
	if (env->philo_num > 2047)
		return (ft_putstr_fd("Error: too many philo\n", 2));
	if ((argv[5] && env->must_eat == 0) || env->error == true)
		return (ft_putstr_fd("Error: Wrong argument type\n", 2));
	if (env->philo_num == 0 || env->time_to_die == 0
		|| env->time_to_eat == 0 || env->time_to_sleep == 0)
		return (ft_putstr_fd("Error: Wrong argument type\n", 2));
	return (0);
}
