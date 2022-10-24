/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recast_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:27:48 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/24 18:20:01 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	my_mlx_pixel_put(t_global *d, int x, int y, int color)
{
	char	*dst;

	dst = d->mlx->addr + (y * d->mlx->line_len + x * (d->mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

void	getDrawLines(t_global *d)
{
		if(!d->ray->side)
			d->ray->sizeRay = (d->ray->sideDistX - d->ray->deltaDistX);
		else
			d->ray->sizeRay = (d->ray->sideDistY - d->ray->deltaDistY);
		d->ray->lineH = (int)(HEIGHT / d->ray->sizeRay);
		d->ray->drawStart = (-d->ray->lineH / 2 ) + (HEIGHT / 2);
		if(d->ray->drawStart < 0)
			d->ray->drawStart = 0;
		d->ray->drawEnd = (d->ray->lineH / 2) + (HEIGHT / 2);
		if(d->ray->drawEnd >= HEIGHT)
			d->ray->drawEnd = HEIGHT - 1;
}

void	initRay(t_global *d, int x)
{
		d->player->camX = 2 * x / (double)WIGHT - 1;
		d->ray->rayDirX = d->player->dirX + d->player->screenX * d->player->camX;
		d->ray->rayDirY = d->player->dirY + d->player->screenY * d->player->camX;

		d->ray->mapX = (int)d->player->posX;
		d->ray->mapY = (int)d->player->posY;

		d->ray->deltaDistX = sqrt(1 + (d->ray->rayDirY * d->ray->rayDirY) \
			/ (d->ray->rayDirX * d->ray->rayDirX));
		d->ray->deltaDistY = sqrt(1 + (d->ray->rayDirX * d->ray->rayDirX) \
			/ (d->ray->rayDirY * d->ray->rayDirY));	
}

void	initImg(t_global *d, t_wall *curWall)
{
	d->ray->curWall = curWall;
	d->ray->texW = curWall->sizeX;
	d->ray->texH = curWall->sizeY;
	d->ray->ptr = curWall->ptr;
}

void	initTex(t_global *d)
{
	d->ray->texY = 0;
	if(!d->ray->side && d->ray->jumpX == 1)
	{
		d->ray->hitpt = \
		d->player->posY + d->ray->sizeRay * d->ray->rayDirY;
		initImg(d, d->map->wallW);
	}
	else if (!d->ray->side)
	{
		d->ray->hitpt = \
		d->player->posY + d->ray->sizeRay * d->ray->rayDirY;
		initImg(d, d->map->wallE);//E
	}
	else if(d->ray->jumpY == -1)
	{
		d->ray->hitpt = \
		d->player->posX + d->ray->sizeRay * d->ray->rayDirX;
		initImg(d, d->map->wallS);//S
	}
	else
	{
		d->ray->hitpt = \
		d->player->posX + d->ray->sizeRay * d->ray->rayDirX;
		initImg(d, d->map->wallN);//N
	}
}
