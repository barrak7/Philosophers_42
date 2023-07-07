/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:10:47 by hbarrak           #+#    #+#             */
/*   Updated: 2023/04/06 16:08:44 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_eat(t_vars *vars)
{
	int	*args;

	args = vars->data->args;
	if (vars->i % 2)
		lock_odd(vars);
	else
		lock_even(vars);
	pthread_mutex_lock(&vars->state);
	vars->last_meal = get_time();
	pthread_mutex_unlock(&vars->state);
	ph_write(vars, 0);
	p_sleep(vars->data->args[TTE]);
	pthread_mutex_unlock(&vars->data->forks[vars->i - 1]);
	pthread_mutex_unlock(&vars->data->forks[(vars->i % args[NOP])]);
}

void	ph_sleeping(t_vars *vars)
{
	ph_write(vars, 2);
	p_sleep(vars->data->args[TTS]);
}

void	*start_routine(void *arg)
{
	int		i;
	t_vars	*vars;

	vars = (t_vars *)arg;
	i = vars->data->args[NOME];
	while (i)
	{
		ph_eat(vars);
		ph_write(vars, 1);
		ph_sleeping(vars);
		if (i > 0)
			i--;
	}
	pthread_mutex_lock(&vars->state);
	vars->finished = 1;
	pthread_mutex_unlock(&vars->state);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_vars	*vars;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->args = malloc(5 * sizeof(int));
	if (!data->args)
		return (1);
	if (philo_pars(argc, argv, data->args))
		return (write(2, "Invalid arguments passed!\n", 26));
	vars = malloc(sizeof(t_vars) * data->args[NOP]);
	if (!vars || init(data, vars))
		return (1);
	if (start_threads(vars))
		return (1);
	monitor_philos(vars);
	return (0);
}
