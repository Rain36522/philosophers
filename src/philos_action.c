/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:37:12 by pudry             #+#    #+#             */
/*   Updated: 2023/12/14 16:05:32 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// 1 = before eating, 2 = before sleeping
int	ft_is_die(t_philo *philo)
{
	int	itime_last_eat;
	int	itime_last_sleep;
	int	i;

	itime_last_eat = (int)time_to_ms() - (int)philo->ilast_eat;
	itime_last_sleep = (int)time_to_ms() - philo->ilast_sleep;
	if (itime_last_eat + philo->t_eat > philo->t_die)
		ft_usleep(philo->t_die - itime_last_eat);
	else if (itime_last_sleep + philo->t_sleep > philo->t_die)
		ft_usleep(philo->t_die - itime_last_sleep);
	else
		return (0);
	i = *philo->irun;
	*philo->irun = 0;
	if (i != *philo->irun)
		printf("%u %i died\n", time_to_ms() - philo->istrt, philo->philo_id);
	return (1);
}

int	ft_philo_sleep(t_philo *philo)
{
	if (ft_is_die(philo))
		return (0);
	printf("%u %i is sleeping\n", time_to_ms() - philo->istrt, philo->philo_id);
	ft_usleep(philo->t_sleep);
	philo->ilast_sleep = time_to_ms();
	return (1);
}

int	ft_philo_think(t_philo *philo)
{
	printf("%u %i is thinking\n", time_to_ms() - philo->istrt, philo->philo_id);
	if (ft_is_die(philo))
			return (0);
	while(philo->ifork < 2 && *philo->irun)
	{
		if (philo->ileft_fork && philo->iright_fork && *philo->iright_fork)
		{
			pthread_mutex_lock(&philo->mutex_id);
			philo->ileft_fork = 0;
			*philo->iright_fork = 0;
			pthread_mutex_unlock(&philo->mutex_id);
			philo->ifork += 2;
			printf("%u %i has taken a fork\n", time_to_ms() - philo->istrt, philo->philo_id);
			printf("%u %i has taken a fork\n", time_to_ms() - philo->istrt, philo->philo_id);
		}
	}
	return (1);
}

int	ft_philo_eat(t_philo *philo)
{
	if (ft_is_die(philo))
			return (0);
	printf("%u %i is eating\n", time_to_ms() - philo->istrt, philo->philo_id);
	ft_usleep(philo->t_eat);
	philo->ilast_eat = time_to_ms();
	pthread_mutex_lock(&philo->mutex_id);
	philo->ileft_fork = 1;
	*philo->iright_fork = 1;
	pthread_mutex_unlock(&philo->mutex_id);
	philo->ifork = 0;
	return (1);
}
