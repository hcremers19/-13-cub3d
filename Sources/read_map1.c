/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:47:15 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/28 16:13:39 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	alloc_map(t_global *d)
{
	int	i;

	d->map->matrix = (char **)malloc(sizeof(char *) * d->map->map_height);
	if (!d->map->matrix)
		ft_exit(d, ER_MA);
	i = 0;
	while (i <= d->map->map_height)
	{
		d->map->matrix[i] = (char *)malloc(sizeof(char) * d->map->map_width);
		if (!d->map->matrix[i])
		{
			while (i >= 0)
				free(d->map->matrix[i--]);
			free(d->map->matrix);
			ft_exit(d, ER_MA);
		}
		i++;
	}
}

/* ----------------------------------------------------------------------------
La fonction alloc_map initialise le tableau à 2 dimensions "matrix" en lui al-
louant juste assez de mémoire pour plus tard y insérer la map.
---------------------------------------------------------------------------- */

void	get_dimensions2(t_global *d, char *line, int fd)
{
	char	*trim;
	int		len;

	trim = ft_strtrim(line, "\n");
	free(line);
	d->map->map_height = 0;
	d->map->map_width = ft_strlen(trim);
	while (trim)
	{
		d->map->map_height++;
		len = ft_strlen(trim);
		if (d->map->map_width < len)
			d->map->map_width = len;
		free(trim);
		line = get_next_line(fd);
		trim = ft_strtrim(line, "\n");
		free(line);
	}
	free(trim);
}

void	get_dimensions1(t_global *d, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 1 || fd > OPEN_MAX || read(fd, NULL, 0) < 0)
		ft_exit(d, ER_OP);
	line = get_next_line(fd);
	i = 0;
	while (i < d->flags->lines)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (!line)
	{
		free(line);
		close(fd);
		ft_exit(d, ER_NM);
	}
	get_dimensions2(d, line, fd);
	close(fd);
}

/* ----------------------------------------------------------------------------
La fonction get_dimensions a dû être coupée en 2 à cause de la Norme.
Elle consiste à parcourir une première fois la map texte afin de déterminer la
hauteur et la largeur du rectangle brut dans lequel est inscrite la map. On dé-
termine la hauteur avec le nombre de lignes qui ont été lues la largeur avec la
taille de la ligne la plus longue ayant été lue.
Ces valeurs permettront plus tard d'allouer juste assez de mémoire pour la mat-
rice.
Les lignes de texte sont lues avec get_next_line.
Le flag "lines" correspond au nombre de lignes à passer dans le fichier de con-
figuration pour atteindre directement les lignes qui concernent la map et igno-
rer celle des textures.
L'utilisation d'une variable temporaire "trim" était nécessaire pour pouvoir
free le retour de ft_strtrim.
---------------------------------------------------------------------------- */

void	read_map(t_global *d, char *file)
{
	get_dimensions1(d, file);
	alloc_map(d);
	fill_matrix1(d, file);
	valid_map(d);
}
