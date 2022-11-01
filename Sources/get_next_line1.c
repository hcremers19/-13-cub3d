/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:39:45 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/01 16:45:15 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

#define BUFFER_SIZE 1

char	*ft_keepend(t_global *d, char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	dest = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!dest)
		ft_free_two_exit(d, &str, NULL, ER_MA);
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

char	*ft_keepstart(t_global *d, char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	dest = ft_calloc(i + 1, sizeof(char));
	if (!dest)
		ft_free_two_exit(d, &str, NULL, ER_MA);
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

char	*sub_gnl(t_global *d, char **stat)
{
	char	*r;
	char	*temp;

	r = ft_keepstart(d, *stat);
	temp = *stat;
	*stat = ft_keepend(d, temp);
	ft_free(&temp);
	return (r);
}

char	*get_next_line(t_global *d, int fd)
{
	static char	*stat;
	int			rd;
	char		*buf;

	rd = BUFFER_SIZE;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX - 2)
		ft_exit(d, ER_OP);
	while (rd > 0)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			ft_exit(d, ER_MA);
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			ft_free_two_exit(d, &buf, &stat, ER_RF);
		stat = ft_strjoin(stat, buf);
		if (!stat)
			ft_free_two_exit(d, &buf, &stat, ER_MA);
		if (ft_srch_nl(stat) != -1)
			break ;
	}
	return (sub_gnl(d, &stat));
}
