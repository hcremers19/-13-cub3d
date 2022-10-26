/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initWalls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:49:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/26 04:34:49 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

static int	findFormat(char *str, char *set)
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

void	initOneWall(t_global *d, t_wall *wall)
{
	int	fd;

	fd = open(wall->path, O_RDONLY);
	if(fd <= 0)
		ft_exit(d, ER_OP);
	if (!findFormat(wall->path, ".xpm"))
		wall->ptr = mlx_xpm_file_to_image(d->mlx->mlx, wall->path, \
			&wall->sizeX, &wall->sizeY);
	else if (!findFormat(wall->path, ".png"))
		wall->ptr = mlx_png_file_to_image(d->mlx->mlx, wall->path, \
			&wall->sizeX, &wall->sizeY);
	else
		ft_exit(d, ER_EX);
	wall->addr = mlx_get_data_addr(wall->ptr, &wall->bpp, \
		&wall->line_len, &wall->endian);
	close(fd);
}

void	initWalls(t_global *d)
{
	initOneWall(d, d->map->wallN);
	initOneWall(d, d->map->wallS);
	initOneWall(d, d->map->wallE);
	initOneWall(d, d->map->wallW);
}

void	nullWalls(t_global *d)
{
	d->map->wallN = NULL;
	d->map->wallS = NULL;
	d->map->wallE = NULL;
	d->map->wallW = NULL;
}
