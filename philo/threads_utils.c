/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:07:54 by hbarrak           #+#    #+#             */
/*   Updated: 2023/04/06 16:10:39 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	p_sleep(int t)
{
	long	start;

	start = get_time();
	while (get_time() - start < t)
		usleep(10);
}

void	ph_write(t_vars *vars, int j)
{
	long	start_time;

	start_time = vars->start_time;
	pthread_mutex_lock(&vars->data->w_mutex);
	if (j == 0)
		printf("%ldms %d is eating\n", get_time() - start_time, vars->i);
	else if (j == 1)
		printf("%ldms %d is thinking\n", get_time() - start_time, vars->i);
	else if (j == 2)
		printf("%ldms %d is sleeping\n", get_time() - start_time, vars->i);
	else
		printf("%ldms %d has taken a fork\n", get_time() - start_time, vars->i);
	pthread_mutex_unlock(&vars->data->w_mutex);
}

void	lock_odd(t_vars *vars)
{
	int	*args;

	args = vars->data->args;
	pthread_mutex_lock(&vars->data->forks[vars->i - 1]);
	ph_write(vars, 3);
	pthread_mutex_lock(&vars->data->forks[vars->i % args[NOP]]);
	ph_write(vars, 3);
}

void	lock_even(t_vars *vars)
{
	int	*args;

	args = vars->data->args;
	pthread_mutex_lock(&vars->data->forks[vars->i % args[NOP]]);
	ph_write(vars, 3);
	pthread_mutex_lock(&vars->data->forks[vars->i - 1]);
	ph_write(vars, 3);
}
