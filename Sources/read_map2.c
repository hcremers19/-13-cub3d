/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:13:18 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/01 15:18:04 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	valid_map(t_global *d)
{
	int	y;
	int	x;

	y = 0;
	while (y < d->map->map_height)
	{
		x = 0;
		while (x < d->map->map_width)
		{
			if ((y == 0 || x == 0 || y == d->map->map_height - 1 || \
				x == d->map->map_width - 1) && (d->map->matrix[y][x] == '0'))
				ft_exit(d, ER_OM);
			else if ((d->map->matrix[y][x] == '0') && \
				(d->map->matrix[y - 1][x] == ' ' || \
				d->map->matrix[y + 1][x] == ' ' || \
				d->map->matrix[y][x - 1] == ' ' || \
				d->map->matrix[y][x + 1] == ' '))
				ft_exit(d, ER_OM);
			x++;
		}
		y++;
	}
}

/* ----------------------------------------------------------------------------
The valid_map function scans the matrix to make sure that the map is closed,
i.e. that the playable area (0) is entirely surrounded by walls (1).
It therefore checks that no 0 is at the edge of the raw map area, and that no
' ' (non-playable area) is next to a 0.
---------------------------------------------------------------------------- */

void	valid_char(t_global *d, char *line, int x, int y)
{
	if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E' || line[x] == 'W')
	{
		if (d->flags->players)
			ft_exit(d, ER_MP);
		else
		{
			d->flags->players++;
			d->player->orientation = line[x];
			d->player->pos_x = x + 0.20;
			d->player->pos_y = y + 0.20;
			d->map->matrix[y][x] = '0';
		}
	}
	else if (line[x] == '0' || line[x] == '1' || line[x] == ' ')
		d->map->matrix[y][x] = line[x];
	else
		ft_exit(d, ER_IC);
}

/* ----------------------------------------------------------------------------
If the character analyzed by the valid_char function determines the starting
position of the player, the function keeps the orientation and position of the
player, and then replaces that character with a '0'.
Otherwise, it simply copies it into the matrix, assuming it is a valid charac-
ter.
---------------------------------------------------------------------------- */

void	fill_matrix2(t_global *d, char *line, int fd)
{
	int		x;
	int		y;
	int		len;
	char	*trim;

	trim = ft_strtrim(line, "\n");
	free(line);
	y = 0;
	while (y < d->map->map_height)
	{
		len = ft_strlen(trim);
		x = -1;
		while (++x < len)
			valid_char(d, trim, x, y);
		while (x < d->map->map_width)
			d->map->matrix[y][x++] = ' ';
		free(trim);
		line = get_next_line(d, fd);
		trim = ft_strtrim(line, "\n");
		free(line);
		y++;
	}
	free(trim);
}

void	fill_matrix1(t_global *d, char *file)
{
	int		fd;
	int		i;
	char	*line;

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
	fill_matrix2(d, line, fd);
	if (!d->flags->players)
		ft_exit(d, ER_NP);
	close(fd);
}

/* ----------------------------------------------------------------------------
The fill_matrix function had to be cut in 2 because of the Norm.
It goes through the text map a second time in order to extract the characters
and insert them in the 2-dimensional array "matrix".
As in get_dimensions, the first lines of the file are ignored using the "lines"
flag. The following lines are then read with get_next_line and the characters
are copied one by one into the matrix, ignoring the line break if there is one.
For lines smaller than the width of the rectangle, the missing memory spaces
are filled with ' ', which corresponds to the cells outside the playable area.
---------------------------------------------------------------------------- */
