/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 16:42:45 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/17 19:19:41 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H
# define _PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define PHILO_MAX	200
# define MS_THREAD		1000
# define MS_MAIN		500
# define MS_DEATH		5

typedef enum		e_state
{
	EATING,
	SLEEPING,
	THINKING,
	RUNNING,
	FINISHED
}					t_state;

typedef struct		s_fork
{
	int				owner;
	int				used;
	pthread_mutex_t	ex;
}					t_fork;

typedef	struct		s_philo
{
	int				id;
	int				nbr_eat;
	int				eat_start;
	pthread_mutex_t	eat_ex;
	t_state			state;
	t_fork			fork;
	pthread_t		thread;
	struct s_info	*info;
}					t_philo;

typedef struct		s_info
{
	int				number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	t_state			state;
	pthread_mutex_t	print_ex;
	pthread_mutex_t	start_ex;
	t_philo			lst_philo[PHILO_MAX];
}					t_info;

/*
** main
*/

int					ft_parsing(t_info *info, char **av, int ac);
void				init_all(t_info *info);

/*
** tests
*/

int					test_philo_death(t_info *info);
int					test_philo_ate_too_much(t_info *info);

/*
** philo
*/

void				*philo_loop(void *arg);
void				philo_display(t_philo *philo, int timestamp, char *msg);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo, t_philo *next);
void				philo_eat(t_philo *philo, t_philo *next);

/*
**	utils
*/

int					str_error(char *msg, int ret);
int					elapsed_time();
void				ft_putnbr(int nb);
void				ft_putstr(int fd, char *str);
int					ft_atoi(const char *str);

#endif
