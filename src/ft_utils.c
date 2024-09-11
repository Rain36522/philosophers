/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:10:06 by pudry             #+#    #+#             */
/*   Updated: 2023/12/13 15:13:45 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

unsigned int	time_to_ms(void)
{
	struct timeval		time;
	unsigned long long	ltime;

	gettimeofday(&time, NULL);
	ltime = time.tv_sec * 100000 + time.tv_usec;
	return (ltime / 1000);
}

void	ft_usleep(int isleep)
{
	unsigned int	istart;

	istart = time_to_ms();
	while ((int)(time_to_ms() - istart) < isleep);
}
