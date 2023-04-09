/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:31:30 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/09 22:49:18 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

typedef struct s_env
{
	size_t			philo_num;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	size_t			must_eat;
	time_t			start_time;
	bool			error;
	size_t			full_philo;
	bool			must_eat_flag;
	bool			dead_flag;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_env;

typedef struct s_philo
{
	size_t			id;
	time_t			last_eat;
	size_t			eat_count;
	size_t			left_fork;
	size_t			right_fork;
	pthread_t		thread;
	t_env			*env;
	bool			error;
}	t_philo;

//libft
bool	ft_isdigit(char c);
size_t	ft_atosize(const char *str, t_env *env);
int		ft_strcmp(const char *s1, const char *s2);

//philo
void	print_mutex(t_philo *philo, char *str);
void	create_philo(t_env *env);
time_t	get_time(void);
bool	check_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_dead(t_philo *philo);

#endif