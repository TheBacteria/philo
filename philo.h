/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:02:21 by mzouine           #+#    #+#             */
/*   Updated: 2024/09/19 12:07:43 by mzouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAHMOUD_H
#define MAHMOUD_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

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
} t_info;

int     mz_parser(int ac, char **av, t_info  *data);
void	putstr_fd(char *msg, int fd);

#endif