/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:39:45 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/28 16:22:20 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*ft_calloc(int count, int size)
{
	char	*rtn;
	int		i;

	rtn = malloc(count * (sizeof(size)));
	if (!rtn)
		return (0);
	i = 0;
	while (i <= count)
		rtn[i++] = 0;
	return (rtn);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (0);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	ft_free(&s1);
	while (s2 && s2[j])
		str[i++] = s2[j++];
	ft_free(&s2);
	str[i] = 0;
	return (str);
}

int	ft_srch_nl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{	
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
