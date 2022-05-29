/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:29:20 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/29 15:07:16 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	ft_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (1);
	return (((time.tv_sec % 10000000) * 1000) + (time.tv_usec / 1000));
}

void	ft_wait(int tm_wait, t_philo *philo, int stat)
{
	unsigned long	cur_time;

	cur_time = ft_current_time();
	if (stat)
	{
		while (ft_current_time() < (cur_time + tm_wait))
			usleep(1);
	}
	else
	{
		while (ft_current_time() < (cur_time + tm_wait))
		{
			usleep(1);
			philo->eat_pt = ft_current_time();
		}
	}
	return ;
}

int	ft_run(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->fork_l)) || ft_message(philo, 1))
		return (ft_error("Error: Mutex lock\n", NULL, 0));
	if (pthread_mutex_lock(&(philo->fork_r)) || ft_message(philo, 1))
		return (ft_error("Error: Mutex lock\n", NULL, 0));
	if (ft_message(philo, 2))
		return (1);
	ft_wait(philo->tm_eat, philo, 0);
	philo->eat_pt = ft_current_time();
	philo->ct_eat++;
	if (pthread_mutex_unlock(&(philo->fork_l))
		|| pthread_mutex_unlock(&(philo->fork_r)))
		return (ft_error("Error: Mutex unlock\n", NULL, 0));
	if (ft_message(philo, 3))
		return (1);
	ft_wait(philo->tm_sleep, philo, 1);
	if (ft_message(philo, 4))
		return (1);
	return (0);
}

void	*ft_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->start = ft_current_time();
	while (*(philo->status)
		&& (philo->nb_eat < 0 || (philo->ct_eat < philo->nb_eat)))
	{
		if (ft_run(philo))
		{
			*(philo->status) = 0;
			return (NULL);
		}
	}
	if (philo->ct_eat == philo->nb_eat)
	{
		if (pthread_mutex_lock(&(philo->meach)))
			ft_error("Error: Mutex lock\n", NULL, 0);
		*(philo->each) += 1;
		if (pthread_mutex_unlock(&(philo->meach)))
			ft_error("Error: Mutex unlock\n", NULL, 0);
	}
	return (NULL);
}
