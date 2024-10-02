/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:02:21 by mzouine           #+#    #+#             */
/*   Updated: 2024/10/02 18:52:25 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAHMOUD_H
#define MAHMOUD_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_fork t_fork;
typedef struct s_philo t_philo;

struct s_timeval
{
    time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
    suseconds_t  tv_usec;  /* and microseconds */
};

typedef struct s_info
{
    int     n_philo;
    int     t_die;
    int     t_eat;
    int     t_sleep;
    int     n_eat;
    int     ac;
    char    **av;
	size_t	timestmp;
	t_philo	**philo;
	t_fork	**fork;
} t_info;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
}					t_fork;


typedef struct s_philo
{
	int		id;
	int     t_die;
    int     t_eat;
    int     t_sleep;
    int     n_eat;
	size_t	timestmp;
	// long long		last_meal;
	int		meals_eaten;
	t_fork			*fork_1;
	t_fork			*fork_2;
	pthread_mutex_t	lock;
	pthread_t		thread;
}					t_philo;


int     mz_parser(int ac, char **av, t_info  *data);
void	putstr_fd(char *msg, int fd);
time_t	get_time(void);
time_t	get_timestamp(t_info *program);
int		mz_usleep(size_t ms);
void	*mz_routine1(void *data);
void	*mz_routine2(void *data);
void	*mz_routineMon(void *data);

#endif