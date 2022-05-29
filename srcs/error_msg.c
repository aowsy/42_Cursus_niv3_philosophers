/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:01:19 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/29 14:43:03 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_message(t_philo *philo, int type)
{
	unsigned long	cur_time;

	if (pthread_mutex_lock(philo->plock))
		return (ft_error("Error: Mutex lock\n", NULL, 0));
	cur_time = ft_current_time();
	if (type == 1)
		printf("%ld %d has taken a fork\n", (cur_time - philo->start),
			(philo->ppos + 1));
	else if (type == 2)
		printf("%ld %d is eating\n", (cur_time - philo->start),
			(philo->ppos + 1));
	else if (type == 3)
		printf("%ld %d is sleeping\n", (cur_time - philo->start),
			(philo->ppos + 1));
	else if (type == 4)
		printf("%ld %d is thinking\n", (cur_time - philo->start),
			(philo->ppos + 1));
	else if (type == 5)
	{
		printf("%ld %d died\n", (cur_time - philo->start), (philo->ppos + 1));
		return (0);
	}
	if (pthread_mutex_unlock(philo->plock))
		return (ft_error("Error: Mutex unlock\n", NULL, 0));
	return (0);
}

int	ft_clean_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&(data->philo[i].fork_r)))
			return (ft_error("Error: Mutex destroy\n", data, 0));
		if (pthread_detach(data->philo[i].pth))
			return (ft_error("Error: Thread detach\n", data, 0));
		i++;
	}
	free(data->philo);
	return (0);
}

//	data->status
int	ft_error(char *str, t_data *data, int stat)
{
	int	i;

	if (!stat)
	{
		i = 0;
		while (str[i])
		{
			write(2, &str[i], 1);
			i++;
		}
	}
	else
	{
		if (pthread_mutex_lock(&(data->plock)))
			return (ft_error("Error: Mutex lock\n", data, 0));
		if (ft_clean_philo(data))
			return (1);
		i = 0;
		while (str[i])
		{
			write(2, &str[i], 1);
			i++;
		}
	}
	return (1);
}
