/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:57:26 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/25 12:47:32 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

// int	d->map->matrix[15][15] =
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

void	mooveN(t_global *d)
{
	if(!d->map->matrix[(int)(d->player->posX + d->player->dirX * SPEED)]\
		[(int)(d->player->posY)])
		d->player->posX += d->player->dirX * SPEED;
	if(!d->map->matrix[(int)(d->player->posX)][(int)(d->player->posY + \
		d->player->dirY * SPEED)])
		d->player->posY += d->player->dirY * SPEED;
}

void	mooveS(t_global *d)
{
	if(!d->map->matrix[(int)(d->player->posX - d->player->dirX * SPEED)]\
		[(int)(d->player->posY)])
		d->player->posX -= d->player->dirX * SPEED;
	if(!d->map->matrix[(int)(d->player->posX)][(int)(d->player->posY + \
		d->player->dirY * SPEED)])
		d->player->posY -= d->player->dirY * SPEED;
}

// PROBLEM AVANCER DANS BONNE DIRECTION

// void	mooveE(t_global *d)
// {
// 	if(!d->map->matrix[(int)(d->player->posX + d->player->dirX * SPEED)]\
// 		[(int)(d->player->posY)])
// 		d->player->posX += d->player->dirY * SPEED;
// 	if(!d->map->matrix[(int)(d->player->posX)][(int)(d->player->posY + \
// 		d->player->dirY * SPEED)])
// 		d->player->posY += d->player->dirX * SPEED;
// }

// void	mooveW(t_global *d)
// {
// 	if(!d->map->matrix[(int)(d->player->posX + d->player->dirX * SPEED)]\
// 		[(int)(d->player->posY)])
// 		d->player->posX -= d->player->dirY * SPEED;
// 	if(!d->map->matrix[(int)(d->player->posX)][(int)(d->player->posY + \
// 		d->player->dirY * SPEED)])
// 		d->player->posY -= d->player->dirX * SPEED;
// }

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
	// if(keycode == A)
	// 	mooveE(d);  
	// if(keycode == D)
	// 	mooveW(d);
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
