/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:44:19 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/09 15:50:25 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_mutex(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->env->print);
	printf("%zu %zu %s\n", \
		get_time() - philo->env->start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->env->print);
}
