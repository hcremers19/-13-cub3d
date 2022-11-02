/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initWalls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:49:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 02:11:01 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Read the end of the wall_path(str) to check its format(*set).
---------------------------------------------------------------------------- */

static int	find_format(char *str, char *set)
{
	int	len;
	int	i;

	len = ft_strlen(str) - 1;
	i = 3;
	while (i >= 0)
	{
		if (str[len] != set[i])
			return (-1);
		len--;
		i--;
	}
	return (0);
}

/* ----------------------------------------------------------------------------
Read the path of the wall's texture, check ".xpm" format and then converts .xpm 
file to a new image instance for each wall.
---------------------------------------------------------------------------- */

void	init_one_wall(t_global *d, t_wall *wall)
{
	int	fd;

	fd = open(wall->path, O_RDONLY);
	if (fd <= 0)
		ft_exit(d, ER_OP);//free matrix
	if (!find_format(wall->path, ".xpm"))
		wall->ptr = mlx_xpm_file_to_image(d->mlx->mlx, wall->path, \
			&wall->size_x, &wall->size_y);
	else
		ft_exit(d, ER_EX);//free matrix
	wall->addr = mlx_get_data_addr(wall->ptr, &wall->bpp, \
		&wall->line_len, &wall->endian);
	close(fd);
}

/* -------------------------
Handle ".png" image format : 
	 if (!find_format(wall->path, ".png"))
		wall->ptr = mlx_png_file_to_image(d->mlx->mlx, wall->path,
		&wall->size_x, &wall->size_y);
------------------------- */

/* ----------------------------------------------------------------------------
Calls "init_one_wall" for each of the 4 walls of the map. 
---------------------------------------------------------------------------- */

void	init_walls(t_global *d)
{
	init_one_wall(d, d->map->wall_n);
	init_one_wall(d, d->map->wall_s);
	init_one_wall(d, d->map->wall_e);
	init_one_wall(d, d->map->wall_w);
}

/* ----------------------------------------------------------------------------
Set initially all of wall structurs pointeurs to NULL to simplificate free.
---------------------------------------------------------------------------- */

void	null_walls(t_global *d)
{
	d->map->wall_n = NULL;
	d->map->wall_s = NULL;
	d->map->wall_e = NULL;
	d->map->wall_w = NULL;
}
