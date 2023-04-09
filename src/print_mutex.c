/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:44:19 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/09 22:53:29 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_mutex(t_philo *philo, char *str)
{
	if (philo->env->dead_flag == true || philo->env->must_eat_flag == true)
		return ;
	pthread_mutex_lock(&philo->env->print);
	if (ft_strcmp(str, "died") == 0)
		philo->env->dead_flag = true;
	if (ft_strcmp(str, "is eating") == 0 \
		&& philo->env->full_philo == philo->env->philo_num)
		philo->env->must_eat_flag = true;
	printf("%zu %zu %s\n", \
		get_time() - philo->env->start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->env->print);
}
