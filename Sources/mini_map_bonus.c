/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:25:35 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/28 18:48:15 by acaillea         ###   ########.fr       */
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
	// int	mapx;
	// int	mapy;
	int	i;
	int	down_y = 3 * HEIGHT / 4;
	int	len_w = (WIDTH / 8) / 11;
	int	len_h = (HEIGHT / 4) / 11;

	y = down_y;// - 11;
	while (++y < (down_y) + (11 * len_h))// - 10)
	{
		x = 0;//9 - 10;
		i = 0;
		while (x <= 11 * len_w)// + 10)
		{
			// Player
			if (x > (5 * len_w) && x < (6 * len_w) && y > (down_y + 5 * len_h) && y < (down_y + (6 * len_h)))
				my_mlx_pixel_put(d, x, y, 0x00FF0000);
			// else if (x % len_w != 0 && y % len_h != 0)
			// 	my_mlx_pixel_put(d, x, y, 0x00FFFFFF);
			else if (x > (i * len_w) && x < ((i + 1) * len_w) && y > (down_y + (i * len_h)) && y < (down_y + (i + 1) * len_h))
				my_mlx_pixel_put(d, x, y, 0x000000FF);
			else
				my_mlx_pixel_put(d, x, y, 0x00000000);
			if (x == (i + 1) * len_w)
				i++;
			x++;
		}
	}
}

// if (x % len == 0 || y % len == 0)
// 	my_mlx_pixel_put(d, x, y, 0x00FFFFFF);
// 	my_mlx_pixel_put(d, x, y, 0x00000000);					
// if (x % ((WIDTH / 8) / 11) == 0)// || y % ((HEIGHT / 4) / 11) == 0)
// else if (x == WIDTH / 16 && y == 3 * HEIGHT / 8)
// 	my_mlx_pixel_put(d, x, y, 0x00FF0000);
// 	my_mlx_pixel_put(d, x, y, 0x00000000);

// h_square = H / 4;
// w_square = W / 8;
// surface = (H * W) / 32
// len 1 bloc = (W / 8) / 11 (ou (H / 8) / 11)
