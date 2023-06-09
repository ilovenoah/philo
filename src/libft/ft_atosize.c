/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atosize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuok <rmatsuok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:51:52 by rmatsuok          #+#    #+#             */
/*   Updated: 2023/04/09 19:47:11 by rmatsuok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

bool	ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (true);
	return (false);
}

bool	ft_isspaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

static int	check(size_t number, char c)
{
	size_t	i;
	size_t	ov_div;
	size_t	ov_mod;

	ov_div = SIZE_MAX / 10;
	ov_mod = SIZE_MAX % 10;
	i = c - '0';
	if (number > ov_div || (number == ov_div && i > ov_mod))
		return (-1);
	return (1);
}

size_t	ft_atosize(const char *str, t_env *env)
{
	size_t		i;
	size_t		number;

	number = 0;
	i = 0;
	while (ft_isspaces(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (check(number, str[i]) == -1)
		{
			printf("Error: Wrong argument type\n");
			env->error = true;
			return (0);
		}
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number);
}
