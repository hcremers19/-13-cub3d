/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:39:45 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/14 12:04:54 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1
#define __null (void *)0

size_t	ft_strlen(const char *s);

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

char	*ft_keepend(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	dest = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!dest)
		return (0);
	j = 0;
	i++;
	while (str && str[i])
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = 0;
	if (!dest[0])
		ft_free(&dest);
	return (dest);
}

char	*ft_keepstart(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	dest = ft_calloc(i + 1, sizeof(char));
	if (!dest)
		return (0);
	j = 0;
	i++;
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = 0;
	if (!dest[0])
		ft_free(&dest);
	return (dest);
}

char	*sub_gnl(char **stat)
{
	char	*r;
	char	*temp;

	r = ft_keepstart(*stat);
	temp = *stat;
	*stat = ft_keepend(temp);
	ft_free(&temp);
	return (r);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	int			rd;
	char		*buf;

	rd = BUFFER_SIZE;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX - 2)
		return (0);
	while (rd > 0)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (0);
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			ft_free(&buf);
			ft_free(&stat);
			return (0);
		}
		stat = ft_strjoin(stat, buf);
		if (ft_srch_nl(stat) != -1)
			break ;
	}
	return (sub_gnl(&stat));
}
