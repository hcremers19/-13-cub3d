/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:25:35 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/27 16:12:46 by hcremers         ###   ########.fr       */
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

unsigned int	mini_map(t_global *d, int x, int y)
{
	unsigned int	color;
	// (void)x;
	// (void)y;
	// (void)d;

	if (d->map->matrix[y % 4][x % 8] == '1')
		color = 0x00FFFFFF;
	else
		color = 0x00000000;
	return (color);
}
