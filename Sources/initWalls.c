/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initWalls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:49:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/27 16:50:38 by hcremers         ###   ########.fr       */
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

void	init_one_wall(t_global *d, t_wall *wall)
{
	int	fd;

	fd = open(wall->path, O_RDONLY);
	if (fd <= 0)
		ft_exit(d, ER_OP);
	if (!find_format(wall->path, ".xpm"))
		wall->ptr = mlx_xpm_file_to_image(d->mlx->mlx, wall->path, \
			&wall->size_x, &wall->size_y);
	// else if (!find_format(wall->path, ".png"))
	// 	wall->ptr = mlx_png_file_to_image(d->mlx->mlx, wall->path, \
	// 		&wall->size_x, &wall->size_y);
	else
		ft_exit(d, ER_EX);
	wall->addr = mlx_get_data_addr(wall->ptr, &wall->bpp, \
		&wall->line_len, &wall->endian);
	close(fd);
}

void	init_walls(t_global *d)
{
	init_one_wall(d, d->map->wall_n);
	init_one_wall(d, d->map->wall_s);
	init_one_wall(d, d->map->wall_e);
	init_one_wall(d, d->map->wall_w);
}

void	null_walls(t_global *d)
{
	d->map->wall_n = NULL;
	d->map->wall_s = NULL;
	d->map->wall_e = NULL;
	d->map->wall_w = NULL;
}
