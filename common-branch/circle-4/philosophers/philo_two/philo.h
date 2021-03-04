/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:19:10 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 16:07:31 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H
# define _PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

# define PHILO_MAX		200
# define SEM_NAME_SIZE	32
# define MS_MAIN		1000
# define SEM_DISPLAY	"sem_display"
# define SEM_FORKS		"sem_forks"

typedef enum		e_close_sem
{
	CLOSE_SEM,
	NO_CLOSE_SEM
}					t_close_sem;

typedef enum		e_state
{
	EATING,
	SLEEPING,
	THINKING,
	RUNNING,
	FINISHED
}					t_state;

typedef	struct		s_philo
{
	int				id;
	int				nbr_eat;
	int				eat_start;
	sem_t			*eating_sem;
	t_state			state;
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
	sem_t			*print_sem;
	sem_t			*forks;
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
void				philo_think(t_philo *philo);
void				philo_eat(t_philo *philo);

/*
**	utils
*/

int					str_error(char *msg, int ret);
int					elapsed_time();
void				ft_putnbr(int nb);
void				ft_putstr(int fd, char *str);
void				ft_append_str(char *s1, char *s2);
int					ft_atoi(const char *str);
void				ft_itoa(char *str, int nb);

/*
**	sem
*/

void				fill_eating_sem_name(int id, char *name);
void				sem_n_post(sem_t *sem, int n);
void				clean_sem(t_info *info, t_close_sem close);

#endif
