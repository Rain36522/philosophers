/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:46:26 by pudry             #+#    #+#             */
/*   Updated: 2023/12/14 13:46:26 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_free_philo(t_philo	*philo)
{
	while (philo)
	{
		free(philo);
		philo = philo->next;
	}
	return (NULL);
}

static t_philo	*gen_philo(t_data *data)
{
	t_philo		*philo;

	philo = (t_philo *) malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->t_eat = data->t_eat;
	philo->t_sleep = data->t_sleep;
	philo->n_eat = data->n_eat;
	philo->irun = &data->irun;
	philo->t_die = data->t_die;
	philo->ileft_fork = 1;
	philo->next = NULL;
	philo->istrt = data->istart_time;
	philo->philo_id = 1;
	philo->ifork = 0;
	philo->ieat = 0;
	philo->ileft_fork = 1;
	philo->iright_fork = NULL;
	philo->ilast_eat = time_to_ms();
	philo->ilast_sleep = time_to_ms();
	return (philo);
}

static t_philo	*philo_add_back(t_data *data, t_philo *philo)
{
	t_philo	*mem_philo;

	if (!philo)
		return (gen_philo(data));
	mem_philo = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = gen_philo(data);
	if (!philo->next)
		return (ft_free_philo(mem_philo));
	philo->next->iright_fork = &philo->ileft_fork;
	philo->next->philo_id = philo->philo_id + 1;
	return (mem_philo);	
}

t_philo	*creat_philo(t_data *data)
{
	int		i;
	t_philo	*philo;
	t_philo	*mem_philo;

	i = 0;
	philo = NULL;
	while (i < data->ifork)
	{
		philo = philo_add_back(data, philo);
		if (!philo)
			return (NULL);
		i ++;
		ft_put_philo(philo);
	}
	if (data->ifork == 1)
	{
		philo->iright_fork = NULL;
		return (philo);
	}
	mem_philo = philo;
	while (philo->next)
		philo = philo->next;
	mem_philo->iright_fork = &philo->ileft_fork;
	return (mem_philo);
}
