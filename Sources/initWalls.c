/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initWalls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:49:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 15:45:21 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

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
Read the end of the wall_path(str) to check its format(*set).
---------------------------------------------------------------------------- */

void	init_one_wall(t_global *d, t_wall *wall)
{
	int	fd;

	fd = open(wall->path, O_RDONLY);
	if (fd <= 0)
		ft_exit_destroy(d, ER_OP, 1);
	if (!find_format(wall->path, ".xpm"))
	{
		wall->ptr = mlx_xpm_file_to_image(d->mlx->mlx, wall->path, \
			&wall->size_x, &wall->size_y);
		if (!wall->ptr)
			ft_exit_destroy(d, ER_MLX_IM, 1);
	}
	else
		ft_exit_destroy(d, ER_EX, 1);
	wall->addr = mlx_get_data_addr(wall->ptr, &wall->bpp, \
		&wall->line_len, &wall->endian);
	if (!wall->addr)
		ft_exit_destroy(d, ER_MLX_AD, 1);
	close(fd);
}

/* -------------------------
Handle ".png" image format : 
	 if (!find_format(wall->path, ".png"))
		wall->ptr = mlx_png_file_to_image(d->mlx->mlx, wall->path,
		&wall->size_x, &wall->size_y);
------------------------- */

/* ----------------------------------------------------------------------------
Read the path of the wall's texture, check ".xpm" format and then convert .xpm 
file to a new image instance for each wall.
---------------------------------------------------------------------------- */

void	init_walls(t_global *d)
{
	init_one_wall(d, d->map->wall_n);
	init_one_wall(d, d->map->wall_s);
	init_one_wall(d, d->map->wall_e);
	init_one_wall(d, d->map->wall_w);
}

/* ----------------------------------------------------------------------------
Calls "init_one_wall" for each of the 4 walls of the map. 
---------------------------------------------------------------------------- */

void	null_walls(t_global *d)
{
	d->map->wall_n = NULL;
	d->map->wall_s = NULL;
	d->map->wall_e = NULL;
	d->map->wall_w = NULL;
}

/* ----------------------------------------------------------------------------
Set initially all of wall structures pointers to NULL to simplify free.
---------------------------------------------------------------------------- */
