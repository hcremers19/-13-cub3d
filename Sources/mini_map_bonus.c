/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:25:35 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/27 19:16:25 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	printBlock(t_global *d, int x, int y, int color)
{
	int	p;
	int	k;

	k = y / (d->map->map_height);
	while (++k < ((y + 1) / (d->map->map_height)))
	{
		p = x / (d->map->map_width);
		while (++p < ((x + 1) / d->map->map_width))
			my_mlx_pixel_put(d, p, k, color);
	}				
}

void	drawMap2D(t_global *d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < d->map->map_height)
	{
		x = -1;
		while (++x < d->map->map_width)
		{
			if (d->map->matrix[y][x] == '1')
				printBlock(d, x, y, 0x00FFFFFF);
			else
				printBlock(d, x, y, 0x00000000);
		}
	}
}

void	draw_mini_map(t_global *d) // draw square
{
	int	y;
	int	x;

	y = (3 * HEIGHT / 4) - 11;
	while (++y < HEIGHT - 10)
	{
		x = 9;
		while (++x < (WIDTH / 8) + 10)
		{
			my_mlx_pixel_put(d, x, y, 0x00FFFFFF);
		}
	}
}

// h_square = H / 4;
// w_square = W / 8;
// surface = (H * W) / 32
// len 1 bloc = W / (8 * 11) (ou H / 8 * 11)
