/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:29:20 by mdelforg          #+#    #+#             */
/*   Updated: 2022/06/03 08:54:46 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	ft_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (((time.tv_sec % 10000000) * 1000) + (time.tv_usec / 1000));
}

void	ft_wait(int tm_wait)
{
	unsigned long	cur_time;

	cur_time = ft_current_time();
	while (ft_current_time() < (cur_time + tm_wait))
		usleep(100);
	return ;
}

int	ft_run(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork_l))
		return (ft_error("Error: Mutex lock\n", NULL, 0));
	if (ft_message(philo, 1))
		return (1);
	if (pthread_mutex_lock(&(philo->fork_r)))
		return (ft_error("Error: Mutex lock\n", NULL, 0));
	if (ft_message(philo, 1))
		return (1);
	if (ft_message(philo, 2))
		return (1);
	philo->eat_pt = ft_current_time();
	if (!philo->eat_pt)
		return (1);
	ft_wait(philo->tm_eat);
	philo->ct_eat++;
	if (pthread_mutex_unlock(philo->fork_l)
		|| pthread_mutex_unlock(&(philo->fork_r)))
		return (ft_error("Error: Mutex unlock\n", NULL, 0));
	if (ft_message(philo, 3))
		return (1);
	ft_wait(philo->tm_sleep);
	if (ft_message(philo, 4))
		return (1);
	return (0);
}

int	ft_incr_each(t_philo *philo)
{
	if (pthread_mutex_lock(philo->m_each))
		return (ft_error("Error: Mutex lock\n", NULL, 0));
	*(philo->each) += 1;
	if (pthread_mutex_unlock(philo->m_each))
		return (ft_error("Error: Mutex unlock\n", NULL, 0));
	return (0);
}

void	*ft_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->start = ft_current_time();
	if (philo->ppos % 2)
		usleep(300);
	while (*(philo->status)
		&& (philo->nb_eat < 0 || (philo->ct_eat < philo->nb_eat)))
	{
		if (ft_run(philo))
		{
			*(philo->status) = 1;
			return (NULL);
		}
	}
	if (philo->ct_eat == philo->nb_eat)
		ft_incr_each(philo);
	return (NULL);
}
