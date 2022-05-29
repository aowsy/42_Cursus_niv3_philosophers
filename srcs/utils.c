/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:32:49 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/29 15:09:50 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (!ft_strchr("+-0123456789", av[i][j]))
				return (1);
		i++;
	}
	return (0);
}

int	ft_parsing(int ac, char **av, t_data *data)
{
	if (ft_check(ac, av))
		return (1);
	data->nb_philo = ft_atoi_philo(av[1]);
	data->tm_die = ft_atoi_philo(av[2]);
	data->tm_eat = ft_atoi_philo(av[3]);
	data->tm_sleep = ft_atoi_philo(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atoi_philo(av[5]);
	else
		data->nb_eat = -1;
	if (data->nb_philo <= 1 || data->nb_philo > 200 || data->tm_die < 60
		|| data->tm_eat < 60 || data->tm_sleep <= 60
		|| (ac == 6 && data->nb_eat < 0))
		return (1);
	data->status = 1;
	data->each = 0;
	return (0);
}

void	ft_fill_philo(t_data *data, int i)
{
	data->philo[i].ct_eat = 0;
	data->philo[i].tm_die = data->tm_die;
	data->philo[i].tm_eat = data->tm_eat;
	data->philo[i].tm_sleep = data->tm_sleep;
	data->philo[i].nb_eat = data->nb_eat;
	data->philo[i].ppos = i;
	data->philo[i].status = &(data->status);
	data->philo[i].plock = &(data->plock);
	data->philo[i].eat_pt = ft_current_time();
	data->philo[i].each = &(data->each);
	data->philo[i].meach = data->philo[0].meach;
	return ;
}

int	ft_philo_init(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (ft_error("Error: Malloc\n", data, 0));
	if (pthread_mutex_init(&(data->plock), NULL))
		return (ft_error("Error: Mutex init\n", data, 0));
	if (pthread_mutex_init(&(data->philo[0].meach), NULL))
		return (ft_error("Error: Mutex init\n", data, 0));
	i = 0;
	while (i < data->nb_philo)
	{
		if (i)
			data->philo[i].fork_l = data->philo[i - 1].fork_r;
		if (pthread_mutex_init(&(data->philo[i].fork_r), NULL))
			return (ft_error("Error: Mutex\n", data, 0));
		ft_fill_philo(data, i);
		i++;
	}
	data->philo[0].fork_l = data->philo[data->nb_philo - 1].fork_r;
	return (0);
}
