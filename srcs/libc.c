/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelforg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:42:10 by mdelforg          #+#    #+#             */
/*   Updated: 2022/05/29 10:02:26 by mdelforg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

unsigned long long	ft_atoi_bis(const char *str, int neg)
{
	size_t				i;
	unsigned long long	temp;

	i = 0;
	temp = 0;
	while (str[i] && ft_strchr("0123456789", str[i]))
	{
		temp *= 10;
		temp += str[i] - '0';
		i++;
		if (temp > INT_MAX && neg < 0)
			return (0);
		else if (temp > INT_MAX && neg > 0)
			return (-1);
	}
	if (str[i])
		return (0);
	return (temp);
}

int	ft_atoi_philo(const char *str)
{
	size_t		i;
	int			neg;
	int			res;

	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	neg = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	if (str[i] < '0' && str[i] > '9')
		return (0);
	res = (int)ft_atoi_bis(&str[i], neg) * neg;
	return (res);
}
