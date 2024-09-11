/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:08:37 by pudry             #+#    #+#             */
/*   Updated: 2023/12/14 16:08:54 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) < ft_strlen(s2))
		return (0);
	while (s1[i] && s1[i] == s2[i])
	{
		i ++;
	}
	return (s1[i] - s2[i]);
}

static int	ft_check_int(char *str)
{
	char	*mem_str;

	mem_str = str;
	while (*mem_str && *mem_str >= '0' && *mem_str <= '9')
		mem_str ++;
	if (!*str || *mem_str)
		return (0);
	else if (ft_strcmp(str, "2147483647") > 0)
		return (0);
	return (1);
}

int	char_to_int(char *str)
{
	unsigned int	i_diz;
	int				i;
	int				ireturn;

	i = 0;
	i_diz = 1;
	ireturn = 0;
	while (str[i + 1])
		i ++;
	while (i >= 0)
	{
		ireturn += (str[i] - '0') * i_diz;
		i_diz *= 10;
		i --;
	}
	return (ireturn);
}

t_data	*treat_input(char **argv)
{
	int		i;
	t_data	*data;

	i = 1;
	while (argv[i])
	{
		if (!ft_check_int(argv[i]))
		{
			printf("Error : Arguemnt invalid %s\n", argv[i]);
			return (NULL);
		}
		i ++;
	}
	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->ifork = char_to_int(argv[1]);
	data->t_die = char_to_int(argv[2]);
	data->t_eat = char_to_int(argv[3]);
	data->t_sleep = char_to_int(argv[4]);
	data->n_eat = 2147483647;
	if (argv[5])
		data->n_eat = char_to_int(argv[5]);
	data->next = NULL;
	return (data);
}
