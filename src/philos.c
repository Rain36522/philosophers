/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:11:42 by pudry             #+#    #+#             */
/*   Updated: 2023/12/14 16:11:42 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*odd_philosopher(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	if (philo->n_eat == 0)
		return (NULL);
	while (*philo->irun)
	{
		if (!i || !*philo->irun || philo->ieat >= philo->n_eat)
			break ;
		i = ft_philo_sleep(philo);
		if (!i || !*philo->irun || !ft_philo_think(philo) || ft_is_die(philo))
			break ;
		printf("%u %i is eating\n", time_to_ms() - philo->istrt, philo->philo_id);
		ft_usleep(philo->t_eat);
		philo->ilast_eat = time_to_ms();
		pthread_mutex_lock(&philo->mutex_id);
		philo->ileft_fork = 1;
		*philo->iright_fork = 1;
		pthread_mutex_unlock(&philo->mutex_id);
		philo->ifork = 0;
		philo->ieat ++;
	}
	return (NULL);
}

void	*even_philosopher(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	if (philo->n_eat == 0)
		return (NULL);
	while (*philo->irun)
	{
		if (!ft_philo_think(philo) || !*philo->irun || ft_is_die(philo))
			break ;
		printf("%u %i is eating\n", time_to_ms() - philo->istrt, philo->philo_id);
		ft_usleep(philo->t_eat);
		philo->ilast_eat = time_to_ms();
		pthread_mutex_lock(&philo->mutex_id);
		philo->ileft_fork = 1;
		*philo->iright_fork = 1;
		pthread_mutex_unlock(&philo->mutex_id);
		philo->ifork = 0;
		philo->ieat ++;
		if (!*philo->irun || philo->ieat >= philo->n_eat)
			break ;
		i = ft_philo_sleep(philo);
		if (!i)
			break ;
	}
	return (NULL);
}

void	launch_philo(t_philo *philo)
{
	while (philo)
	{
		if (philo->philo_id % 2)
		{
			pthread_create(&philo->thread_id, NULL, odd_philosopher, (void *)philo);
		}
		else
		{
			pthread_create(&philo->thread_id, NULL, even_philosopher, (void *)philo);
		}
		if (!philo->next)
			pthread_join(philo->thread_id, NULL);
		philo = philo->next;
	}
}
