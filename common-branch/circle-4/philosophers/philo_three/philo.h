/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:28:36 by ablanc            #+#    #+#             */
/*   Updated: 2020/10/21 16:09:09 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_H
# define _PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <signal.h>

# define PHILO_MAX		200
# define SEM_NAME_SIZE	32
# define MS_THREAD		500
# define SEM_NB			4
# define SEM_DISPLAY	"sem_display"
# define SEM_FORKS		"sem_forks"
# define SEM_DEATH		"sem_death"
# define SEM_END		"sem_end"
# define SEM_EATING		"sem_eating"
# define SEM_EAT_NBR	"sem_eat_nbr"

typedef enum		e_close_sem
{
	CLOSE_SEM,
	NO_CLOSE_SEM
}					t_close_sem;

typedef enum		e_state
{
	RUNNING,
	FINISHED,
	EATING,
	SLEEPING,
	THINKING
}					t_state;

typedef enum		e_sem
{
	print,
	forks,
	death,
	end
}					t_sem;

typedef struct		s_info
{
	int				number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	sem_t			*uni_sem[SEM_NB];
	sem_t			*sem_eating[PHILO_MAX];
	sem_t			*sem_nbr_eat[PHILO_MAX];
}					t_info;

typedef	struct		s_philo
{
	int				id;
	int				eat_start;
	t_state			state;
	t_state			g_state;
	pthread_t		stop_thread;
	pthread_t		death_thread;
}					t_philo;

typedef struct		s_args
{
	t_info			info;
	t_philo			philo;
}					t_args;

/*
** main
*/

int					ft_parsing(t_info *info, char **av, int ac);
void				init_all(t_args *args);

/*
** tests
*/

void				*wait_stop(void *args);
void				*test_philo_death(void *args);
void				*main_wait_end(void *args);

/*
** philo
*/

void				philo_loop(t_args *args);
void				philo_display(t_args *args, int timestamp, char *msg);
void				philo_sleep(t_args *args);
void				philo_think(t_args *args);
void				philo_eat(t_args *args);

/*
**	utils
*/

int					str_error(char *s, int status);
int					elapsed_time();
void				ft_putnbr(int nb);
void				ft_putstr(int fd, char *str);
int					ft_atoi(const char *str);
void				ft_itoa(char *str, int nb);
void				ft_append_str(char *s1, char *s2);

/*
**	sem
*/

void				fill_sem_name(char *name, int id, char *title);
void				sem_n_post(sem_t *sem, int nb);
void				sem_n_wait(sem_t *sem, int nb);
void				clean_sem(t_info *info, t_close_sem close);

#endif
