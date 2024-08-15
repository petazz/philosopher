/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 02:55:00 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/08/15 21:39:59 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	int	i;
	long	num;
	int	signo;

	signo = 1;
	num = 0;
	i = 0;
	//isnum y isint
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			signo *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		num = (num * 10) + (str[i] - '0');
		++i;
	}
	return (num * signo);
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
		usleep(time / 10);
}

void	print_str(char *str, t_philos *philo)
{
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%zu %d %s\n", get_current_time() - philo->data->time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	is_dead(t_philos *philos)
{
	pthread_mutex_lock(&philos->data->dead_lock);
	if (philos->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philos->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philos->data->dead_lock);
	return (0);
}