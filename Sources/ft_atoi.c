/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:10:45 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/29 20:02:14 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_limits(long long n, const char *str, int s)
{
	long long	lim;

	lim = ((n * 10) + (*str - '0')) * s;
	if (lim < -2147483648)
		return (0);
	if (lim > 2147483647)
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned int	n;
	int				s;
	int				i;

	n = 0;
	s = 1;
	i = 0;
	while (str[i] && ((8 < str[i] && str[i] < 14) || str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			s = -1;
	i--;
	while (ft_isdigit(str[++i]))
	{
		if (!ft_limits(n, &str[i], s))
			return (0);
		if (ft_limits(n, &str[i], s) == -1)
			return (-1);
		n = (n * 10) + (str[i] - 48);
	}
	return (n * s);
}
