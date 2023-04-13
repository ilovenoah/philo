/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:31:30 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/13 21:01:33 by rmatsuok         ###   ########.fr       */
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
	size_t			th_num;
	size_t			philo_num;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	size_t			must_eat;
	time_t			start_time;
	size_t			full_philo;
	bool			error;
	bool			must_eat_flag;
	bool			dead_flag;
	pthread_mutex_t	full;
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
	pthread_mutex_t	l_eat;
}	t_philo;

//libft
bool	ft_isdigit(char c);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(char *s);
size_t	ft_atosize(const char *str, t_env *env);
int		ft_strcmp(const char *s1, const char *s2);

//philo
bool	error_check(int argc, char **argv);
int		set_env_data(t_env *env, char **argv);
bool	checkflag(t_philo *philo);
void	*one_philo(t_philo *philo);
void	print_mutex(t_philo *philo, char *str);
void	create_philo(t_env *env);
time_t	get_time(void);
bool	check_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_dead(t_philo *philo);
int		philo_exec(t_env *env, t_philo *philo, pthread_t *th);

#endif