/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:06:19 by pudry             #+#    #+#             */
/*   Updated: 2023/12/14 16:07:58 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_put_philo(t_philo *philo)
{
	while (philo)
	{
		printf ("<=======================================================>\n");
		printf("id : %i\n", philo->philo_id);
		printf("time to eat : %i\n", philo->t_eat);
		printf("time to sleep : %i\n", philo->t_sleep);
		printf("time to die : %i\n", philo->t_die);
		printf("ifork : %i\n", philo->ifork);
		printf("n eat : %i\n", philo->n_eat);
		printf("start time : %u\n", philo->istrt);
		if (philo->iright_fork)
			printf("left : %i, right : %i\n", philo->ileft_fork, *philo->iright_fork);
		printf ("<=======================================================>\n");
		philo = philo->next;
	}
}

static void	ft_free_philo(t_philo *philo)
{
	t_philo	*nxt;

	while (philo)
	{
		nxt = philo->next;
		free(philo);
		philo = nxt;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Error : Arguments invalide");
		return (201);
	}
	data = treat_input(argv);
	if (!data)
		return (12);
	data->istart_time = time_to_ms();
	philo = creat_philo(data);
	launch_philo(philo);
	while (data->irun == 1);
	printf("fini\n");
	free(data);
	ft_free_philo(philo);
	return (0);
}
