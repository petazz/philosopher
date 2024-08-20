/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 02:55:00 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/20 17:18:56 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	num;

	num = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (!ft_isalnum(str[i]))
		return (-1);
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		num = (num * 10) + (str[i] - '0');
		++i;
	}
	if (num > INT_MAX || num < INT_MIN)
		return (-1);
	return (num);
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(10);
}

void	print_str(char *str, t_philos *philo)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (!is_dead(philo))
		printf("%zu %d %s\n", (get_current_time() - philo->data->time),
			philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}
