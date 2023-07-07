/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:59:39 by hbarrak           #+#    #+#             */
/*   Updated: 2023/03/08 20:48:41 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (i && !str[i] && ft_isdigit(str[i - 1]))
		return (1);
	return (0);
}

int	philo_pars(int c, char **argv, int *args)
{
	int	i;

	i = 1;
	if (c > 6 || c < 5)
		return (1);
	while (i < c)
	{
		if (is_num(argv[i]))
		{
			args[i - 1] = ft_atoi(argv[i]);
			if ((i == 1 && args[i - 1] == 0) || args[i - 1] < 0)
				return (1);
		}
		else
			return (1);
		i++;
	}
	if (c == 5)
		args[i - 1] = -1;
	return (0);
}
