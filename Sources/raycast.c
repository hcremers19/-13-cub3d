/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:24:31 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/25 13:23:49 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

// int	map[15][15] =
// {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,1,0,1,0,0,0,0,0,0,1},
// 	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,1,0,0,1,0,1,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// };

//------------------------------------------------------------------

void	getSideDist(t_global *d)
{
	if(d->ray->rayDirX < 0)
	{
		d->ray->jumpX = -1;
		d->ray->sideDistX = (d->player->posX - d->ray->mapX) \
			* d->ray->deltaDistX;
	}
	else
	{
		d->ray->jumpX = 1;
		d->ray->sideDistX = (d->ray->mapX + 1.0 - d->player->posX) \
			* d->ray->deltaDistX;
	}
	if(d->ray->rayDirY < 0)
	{
		d->ray->jumpY = -1;
		d->ray->sideDistY = (d->player->posY - d->ray->mapY) \
			 * d->ray->deltaDistY;
	}
	else
	{
		d->ray->jumpY = 1;
		d->ray->sideDistY = (d->ray->mapY + 1.0 - d->player->posY) \
			* d->ray->deltaDistY;
	}
}

void	hitLoop(t_global *d)
{
	int hit;

	hit = 0;
	while(!hit)
	{
		if(d->ray->sideDistX < d->ray->sideDistY)
		{
			d->ray->sideDistX += d->ray->deltaDistX;
			d->ray->mapX += d->ray->jumpX;
			d->ray->side = 0;
		}
		else
		{
			d->ray->sideDistY += d->ray->deltaDistY;
			d->ray->mapY += d->ray->jumpY;
			d->ray->side = 1;
		}
		if(d->map->matrix[d->ray->mapX][d->ray->mapY] == 1)
			hit = 1;
	}	
}

void	posTex(t_global *d)
{
	d->ray->hitpt -= floor(d->ray->hitpt);
	d->ray->texX = (int)(d->ray->hitpt * (double)d->ray->texW);
	if (d->ray->side == 0 && d->ray->rayDirX > 0)
		d->ray->texX = d->ray->texW - d->ray->texX - 1;
	if (d->ray->side == 1 && d->ray->rayDirY < 0)
		d->ray->texX = d->ray->texW - d->ray->texX - 1;
	d->ray->step = (double)d->ray->texH / d->ray->lineH;
	d->ray->texPos = (d->ray->drawStart - HEIGHT / 2 + d->ray->lineH / 2) \
		* d->ray->step;
}

void	drawVert(t_global *d, int x)
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

void	raycastLoop(t_global *d)
{
	int x;
	
	x = 0;
	while(x < WIGHT)
	{
		initRay(d, x);
		getSideDist(d);
		hitLoop(d);
		getDrawLines(d);
		initTex(d);
		posTex(d);
		drawVert(d, x);
		x++;
	}
}
