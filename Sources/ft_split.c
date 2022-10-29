/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:03:50 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/29 20:04:39 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s;

	i = 0;
	s = ft_strlen(src);
	if (!dstsize)
		return (s);
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s);
}

char	**ft_clean(char **s, int i)
{
	while (i--)
		free(s[i]);
	return (0);
}

int	wrdnbr(t_global *d, char const *s, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		j = 0;
		while (s[i + j] && (s[i + j] != c))
			j++;
		if (j)
			count++;
		i = i + j;
	}
	if (count != 3)
		ft_exit(d, ER_RGB);
	return (count);
}

char	**ft_split2(char const *s, char c, char **tab, unsigned int w)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	m;

	i = 0;
	j = 0;
	while (i < w)
	{
		while (s[j] && (s[j] == c))
			j++;
		m = 0;
		while (s[j + m] && (s[j + m] != c))
			m++;
		tab[i] = malloc(sizeof(char) * (m + 1));
		if (!tab[i])
			return (ft_clean(tab, i));
		ft_strlcpy(tab[i], &s[j], m + 1);
		j = j + m;
		i++;
	}
	return (tab);
}

char	**ft_split(t_global *d, char const *s, char c)
{
	unsigned int	w;
	char			**tab;

	if (!s)
		return (0);
	w = wrdnbr(d, s, c);
	tab = malloc(sizeof(char *) * (w + 1));
	if (!tab)
		return (0);
	tab = ft_split2(s, c, tab, w);
	if (!tab)
	{
		free(tab);
		return (0);
	}
	tab[w] = 0;
	return (tab);
}
