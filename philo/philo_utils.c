/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:59:42 by hbarrak           #+#    #+#             */
/*   Updated: 2023/04/06 16:07:25 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init(t_data *data, t_vars *vars)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->w_mutex, NULL))
		return (write(2, "Error initializing mutex!\n", 26));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args[NOP]);
	if (!data->forks)
		return (1);
	while (i < data->args[NOP])
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (write(2, "Error initializing mutex!\n", 26));
		if (pthread_mutex_init(&vars[i].state, NULL))
			return (write(2, "Error initializing mutex!\n", 26));
		vars[i].finished = 0;
		vars[i].data = data;
		i++;
	}
	data->tr = malloc(sizeof(pthread_t) * data->args[NOP]);
	if (!data->tr)
		return (1);
	return (0);
}

int	start_threads(t_vars *vars)
{
	int		i;
	long	start_time;
	t_data	*data;

	i = 0;
	start_time = get_time();
	while (i < vars->data->args[NOP])
	{
		vars[i].i = i + 1;
		data = vars[i].data;
		vars[i].start_time = start_time;
		vars[i].last_meal = vars->start_time;
		if (pthread_create(&(data->tr[i]), NULL, start_routine, &vars[i]))
			return (write(2, "Error creating thread!\n", 23));
		i++;
	}
	return (0);
}

void	detach_threads(t_vars *vars, int j)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&vars->data->w_mutex);
	printf("%ldms %d died\n", get_time() - vars[j].start_time, j + 1);
	pthread_mutex_unlock(&vars[j].state);
	while (i < vars->data->args[NOP])
	{
		pthread_detach(vars->data->tr[i]);
		i++;
	}
}

void	clean_up(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->data->args[NOP])
	{
		pthread_join(vars->data->tr[i], NULL);
		pthread_mutex_destroy(&vars[i].state);
		pthread_mutex_destroy(&vars->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&vars->data->w_mutex);
}

void	monitor_philos(t_vars *vars)
{
	int	i;
	int	finished;

	p_sleep(vars->data->args[TTD]);
	if (vars->data->args[NOP] == 1)
		return (detach_threads(vars, 0));
	while (1)
	{
		i = 0;
		finished = 0;
		while (i < vars->data->args[NOP])
		{
			pthread_mutex_lock(&vars[i].state);
			if (!vars[i].finished && get_time()
				- vars[i].last_meal > vars[i].data->args[TTD])
				return (detach_threads(vars, i));
			if (vars[i].finished)
				finished++;
			pthread_mutex_unlock(&vars[i].state);
			i++;
		}
		if (finished >= vars->data->args[NOP])
			break ;
	}
	clean_up(vars);
}
