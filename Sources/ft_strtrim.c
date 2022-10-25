/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:14:47 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/25 14:59:48 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (0);
	if (len > (ft_strlen(s) - start - 1))
		len = ft_strlen(s) - start;
	if (ft_strlen(s) - 1 < start)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	while (s[++i])
		if (i >= start && j < len)
			str[j++] = s[i];
	str[j] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	const char	*r;
	int			i;

	i = 0;
	if (!c)
	{
		r = s + ft_strlen(s);
		return ((char *)r);
	}
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			r = s + i;
			return ((char *)r);
		}
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
