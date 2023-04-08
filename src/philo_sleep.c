/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsuokaryou <matsuokaryou@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:33:56 by matsuokaryo       #+#    #+#             */
/*   Updated: 2023/04/07 18:35:49 by matsuokaryo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_sleep(t_philo *philo)
{
	time_t	start;
	time_t	end;

	start = get_time();
	end = start;
	while (end - start < philo->env->time_to_sleep)
	{
		usleep(100);
		end = get_time();
	}
}