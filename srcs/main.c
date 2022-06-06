/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:41:25 by mdelforg          #+#    #+#             */
/*   Updated: 2022/06/02 12:06:06 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_detach(data->philo[i].pth))
			return (ft_error("Error: Tread detach\n", data, 1));
		i++;
	}
	return (0);
}

int	ft_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(data->philo[i].pth), NULL, &ft_routine,
				&(data->philo[i])))
			return (ft_error("Error: Tread create\n", data, 1));
		i++;
	}
	return (0);
}

int	ft_monito(t_data *data)
{
	int				i;
	unsigned long	cur_time;

	while (data->status && data->each < data->nb_philo)
	{
		i = 0;
		while (i < data->nb_philo && data->status)
		{
			cur_time = ft_current_time();
			if (cur_time > (data->philo[i].eat_pt + data->tm_die)
				&& (data->nb_eat < 0 || data->philo[i].ct_eat != data->nb_eat))
			{
				data->status = 0;
				ft_message(&(data->philo[i]), 5);
				return (0);
			}
			i++;
		}
	}
	if (data->each == data->nb_philo)
		printf("Everybody ate %d times\n", data->nb_eat);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (ft_error("Error: Argument\n", &data, 0));
	if (ft_parsing(ac, av, &data))
		return (ft_error("Error: Argument\n", &data, 0));
	if (ft_philo_init(&data))
		return (1);
	if (ft_start(&data))
	{
		ft_clean_philo(&data);
		return (1);
	}
	ft_monito(&data);
	if (ft_end(&data))
		return (1);
	if (ft_clean_philo(&data))
		return (1);
	pthread_mutex_destroy(&(data.m_each));
	pthread_mutex_destroy(&(data.plock));
	usleep(300);
	system("leaks philo");
	return (0);
}
