/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:10:20 by hbarrak           #+#    #+#             */
/*   Updated: 2023/04/06 16:11:09 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NOP 0
# define TTD 1
# define TTE 2
# define TTS 3
# define NOME 4

typedef struct s_data
{
	pthread_t			*tr;
	pthread_mutex_t		*forks;
	pthread_mutex_t		w_mutex;
	int					*args;
}						t_data;
typedef struct s_vars
{
	long				last_meal;
	int					i;
	int					finished;
	pthread_mutex_t		state;
	long				start_time;
	t_data				*data;
}						t_vars;

int						ft_isdigit(char c);
int						is_num(char *str);
int						ft_atoi(const char *str);
int						philo_pars(int c, char **argv, int *args);
int						init(t_data *data, t_vars *vars);
long					get_time(void);
void					p_sleep(int t);
void					ph_write(t_vars *vars, int j);
void					*start_routine(void *arg);
int						start_threads(t_vars *vars);
void					detach_threads(t_vars *vars, int j);
void					clean_up(t_vars *vars);
void					monitor_philos(t_vars *vars);
void					lock_odd(t_vars *vars);
void					lock_even(t_vars *vars);

#endif
