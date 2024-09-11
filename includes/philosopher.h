/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:22:23 by pudry             #+#    #+#             */
/*   Updated: 2023/12/14 14:22:39 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHER_H
# define PHILOSPHER_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

# define DEBUG printf("\033[1;31m%s:%d\n\033[0;37m", __FILE__, __LINE__);

typedef struct s_data {
	int				ifork;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				irun;
	unsigned int	istart_time;
	struct s_data	*next;
}	t_data;

typedef struct s_philo {
	int				philo_id;
	unsigned int	istrt;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	unsigned int	ilast_eat;
	unsigned int	ilast_sleep;
	int				ieat;
	int				ifork;
	int				n_eat;
	int				ileft_fork;
	int				*iright_fork;
	int				*irun;
	struct s_philo	*next;
	pthread_t		thread_id;
	pthread_mutex_t	mutex_id;
}	t_philo;

t_data			*treat_input(char **argv);
t_philo			*creat_philo(t_data *data);
void			ft_put_philo(t_philo *philo);
int				ft_philo_sleep(t_philo *philo);
int				ft_philo_think(t_philo *philo);
int				ft_philo_eat(t_philo *philo);


unsigned int	ft_strlen(char *str);
void			ft_usleep(int isleep);
unsigned int	time_to_ms(void);

void			launch_philo(t_philo *philo);
int				ft_philo_sleep(t_philo *philo);
int				ft_philo_think(t_philo *philo);
// int				ft_philo_eat(t_philo *philo);
int				ft_is_die(t_philo *philo);

#endif