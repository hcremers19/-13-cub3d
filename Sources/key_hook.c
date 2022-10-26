/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:57:26 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/26 03:03:43 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	mooveN(t_global *d)
{
	if (d->map->matrix[(int)(d->player->posY + d->player->dirY * SPEED)]\
		[(int)(d->player->posX)] != '1')
		d->player->posY += d->player->dirY * SPEED;
	if (d->map->matrix[(int)(d->player->posY)][(int)(d->player->posX + \
		d->player->dirX * SPEED)] != '1')
		d->player->posX += d->player->dirX * SPEED;
}

void	mooveS(t_global *d)
{
	if (d->map->matrix[(int)(d->player->posY - d->player->dirY * SPEED)]\
		[(int)(d->player->posX)] != '1')
		d->player->posY -= d->player->dirY * SPEED;

	if (d->map->matrix[(int)(d->player->posY)]\
		[(int)(d->player->posX - d->player->dirX * SPEED)] != '1')
		d->player->posX -= d->player->dirX * SPEED;
}

void	mooveE(t_global *d)
{
	if (d->map->matrix[(int)(d->player->posY)]\
		[(int)(d->player->posX - d->player->screenX * SPEED)] != '1')
		d->player->posX -= d->player->screenX * SPEED;
	if (d->map->matrix[(int)(d->player->posY - d->player->screenY * SPEED)]\
		[(int)(d->player->posX)] != '1')
		d->player->posY -= d->player->screenY * SPEED;
}

void	mooveW(t_global *d)
{
	if (d->map->matrix[(int)(d->player->posY)][(int)(d->player->posX + \
		d->player->screenX * SPEED)] != '1')
		d->player->posX += d->player->screenX * SPEED;
	if (d->map->matrix[(int)(d->player->posY + d->player->screenY * SPEED)]\
		[(int)(d->player->posX)] != '1')
		d->player->posY += d->player->screenY * SPEED;
}

void	rotE(t_global *d)
{
	double oldDirX;
	double oldScreenX;

	oldDirX = d->player->dirX;
	d->player->dirX = \
		d->player->dirX * cos(ROT) - d->player->dirY * sin(ROT);
	d->player->dirY = \
		oldDirX * sin(ROT) + d->player->dirY * cos(ROT);
	oldScreenX = d->player->screenX;
	d->player->screenX = \
		d->player->screenX * cos(ROT) - d->player->screenY * sin(ROT);
    d->player->screenY = \
		oldScreenX * sin(ROT) + d->player->screenY * cos(ROT);
}

void	rotW(t_global *d)
{
	double oldDirX;
	double oldScreenX;

	oldDirX = d->player->dirX;
	d->player->dirX = \
		d->player->dirX * cos(-ROT) - d->player->dirY * sin(-ROT);
	d->player->dirY = oldDirX * sin(-ROT) + d->player->dirY * cos(-ROT);
	oldScreenX = d->player->screenX;
	d->player->screenX = \
		d->player->screenX * cos(-ROT) - d->player->screenY * sin(-ROT);
    d->player->screenY = \
		oldScreenX * sin(-ROT) + d->player->screenY * cos(-ROT);
}

int	key_hook(int keycode, t_global *d)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
		ft_exit(d, EXIT_S);
	}
	if (keycode == W)
		mooveN(d);
	if (keycode == S)
		mooveS(d);
	if(keycode == A)
		mooveE(d);  
	if(keycode == D)
		mooveW(d);
	if (keycode == RIGHT_ARR)
		rotE(d);
	if (keycode == LEFT_ARR)
		rotW(d);
	// Laquelle est mieux ?
	mlx_destroy_image(d->mlx->mlx, d->mlx->img);
	// mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	initWindow(d);
	return(0);
}
