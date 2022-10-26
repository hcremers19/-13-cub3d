/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:25:35 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/26 22:42:10 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	printBlock(t_global *d, int x, int y, int color)
{
	int p;
	int k;

	k = y / (d->map->map_height);
	while (++k < ((y + 1) / (d->map->map_height)))
	{
		p = x / (d->map->map_width);
		while (++p < ((x + 1) / d->map->map_width))
			my_mlx_pixel_put(d, p, k, color);
	}				
}

void	drawVertplus(t_global *d, int x)
{
	int				y;
	unsigned int 	color;

	y = -1;
	while(++y < HEIGHT)
	{
		if(y < d->ray->drawStart)
			color = (unsigned int)d->map->ceiling;
		else if(y < d->ray->drawEnd)
		{
			d->ray->texY = (int)d->ray->texPos;
			d->ray->texPos += d->ray->step;
			color = *(unsigned int *)(d->ray->curWall->addr + \
			(d->ray->texY * d->ray->curWall->line_len + \
			d->ray->texX * (d->ray->curWall->bpp / 8)));
		}
		else
			color = (unsigned int)d->map->floor;
		my_mlx_pixel_put(d, x, y, color);
	}
}

void	drawMap2D(t_global *d)
{
	int	x;
	int	y;

	y = -1;
	while(++y < d->map->map_height)
	{
		x = -1;
		while(++x < d->map->map_width)
		{
			if(d->map->matrix[y][x] == '1')
				printBlock(d, x, y, 0x00FFFFFF);
			else
				printBlock(d, x, y, 0x00000000);		
		}
	}
}
