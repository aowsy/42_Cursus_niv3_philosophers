/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:48:39 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/31 17:43:11 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		pth;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*m_each;
	pthread_mutex_t	*plock;
	int				ppos;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				nb_eat;
	int				ct_eat;
	int				*each;
	int				*status;
	unsigned long	start;
	unsigned long	eat_pt;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				nb_eat;
	int				each;
	int				status;
	pthread_mutex_t	plock;
	pthread_mutex_t	m_each;
	t_philo			*philo;
}	t_data;

/*							routine.c						*/
void			*ft_routine(void *param);
unsigned long	ft_current_time(void);

/*							utils.c							*/
int				ft_parsing(int ac, char **av, t_data *data);
int				ft_philo_init(t_data *data);

/*							error_msg.c						*/
int				ft_error(char *str, t_data *data, int stat);
int				ft_message(t_philo *philo, int type);
int				ft_clean_philo(t_data *data);

/*							libc.c							*/
char			*ft_strchr(const char *s, int c);
int				ft_atoi_philo(const char *str);

#endif
