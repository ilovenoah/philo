/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:33:56 by matsuokaryo       #+#    #+#             */
/*   Updated: 2023/04/09 15:55:26 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_sleep(t_philo *philo)
{
	time_t	start;

	print_mutex(philo, "is sleeping");
	start = get_time();
	while (get_time() - start < philo->env->time_to_sleep)
		usleep(100);
}
