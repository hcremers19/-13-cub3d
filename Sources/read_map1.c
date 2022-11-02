/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:47:15 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/02 01:40:36 by I-lan            ###   ########.fr       */
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
	while (i < d->map->map_height)
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
The alloc_map function initializes the 2-dimensional array "matrix" by allocat-
ing it just enough memory for later insertion of the map.
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
		line = get_next_line(d, fd);
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
	if (fd < 1 || fd > FOPEN_MAX || read(fd, NULL, 0) < 0)
		ft_exit(d, ER_OP);
	line = get_next_line(d, fd);
	i = 0;
	while (i < d->flags->lines)
	{
		free(line);
		line = get_next_line(d, fd);
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
The get_dimensions function had to be split in 2 because of the Norm.
It consists in scanning the text map a first time in order to determine the
height and width of the rectangle in which the map is inscribed. The height is
determined by the number of lines that have been read and the width by the
size of the longest line that has been read. These values will later allow to
allocate just enough memory for the matrix.
The text lines are read with get_next_line.
The "lines" flag corresponds to the number of lines to skip in the configura-
tion file to reach directly the lines that concern the map and ignore the tex-
ture ones.
The use of a temporary variable "trim" was necessary to free the return of
ft_strtrim.
---------------------------------------------------------------------------- */

void	read_map(t_global *d, char *file)
{
	get_dimensions1(d, file);
	alloc_map(d);
	fill_matrix1(d, file);
	valid_map(d);
}
