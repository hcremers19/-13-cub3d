/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:12:28 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/11 16:15:36 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*ft_strjoin_gnl(char *line, char buf)
{
	int		i;
	char	*new;

	new = malloc(ft_strlen(line) + 2);
	if (!new)
		return (0);
	i = 0;
	while (line && line[i])
	{
		new[i] = line[i];
		++i;
	}
	if (line)
		free(line);
	new[i++] = buf;
	new[i] = 0;
	return (new);
}

char	*get_next_line(int fd)
{
	char	*line;
	int		ret;
	char	buf[1];

	line = (void *)0;
	while (buf[0] != '\n')
	{
		ret = read(fd, buf, 1);
		line = ft_strjoin_gnl(line, buf[0]);
		if (ret <= 0)
			break ;
	}
	return (line);
}
