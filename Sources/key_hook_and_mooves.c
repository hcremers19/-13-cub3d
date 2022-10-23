/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_and_mooves.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:57:26 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/24 01:37:42 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	map1[10][10] =
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

//------------------------------------------------------------------

void	mooveN(t_global *d)
{
	if(!map1[(int)(d->player->posX + d->player->dirX * SPEED)]\
		[(int)(d->player->posY)])
		d->player->posX += d->player->dirX * SPEED;
	if(!map1[(int)(d->player->posX)][(int)(d->player->posY + \
		d->player->dirY * SPEED)])
		d->player->posY += d->player->dirY * SPEED;
}

void	mooveE(t_global *d)
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

void	mooveS(t_global *d)
{
	if(!map1[(int)(d->player->posX - d->player->dirX * SPEED)]\
		[(int)(d->player->posY)])
		d->player->posX -= d->player->dirX * SPEED;
	if(!map1[(int)(d->player->posX)][(int)(d->player->posY + \
		d->player->dirY * SPEED)])
		d->player->posY -= d->player->dirY * SPEED;
}

void	mooveW(t_global *d)
{
	double oldDirX;
	double oldScreenX;

	oldDirX = d->player->dirX;
	d->player->dirX = d->player->dirX * cos(-ROT) - d->player->dirY * sin(-ROT);
	d->player->dirY = oldDirX * sin(-ROT) + d->player->dirY * cos(-ROT);
		
	oldScreenX = d->player->screenX;
	d->player->screenX = d->player->screenX * cos(-ROT) - d->player->screenY * sin(-ROT);
    d->player->screenY = oldScreenX * sin(-ROT) + d->player->screenY * cos(-ROT);
}

int	key_hook(int keycode, t_global *d)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
		ft_exit(d, "Thanks for playing, bye !\n");
	}
	if (keycode == W)
		mooveN(d);
	if (keycode == D || keycode == RIGHT_ARR)
		mooveE(d);
	if (keycode == S)
		mooveS(d);
	if (keycode == A || keycode == LEFT_ARR)
		mooveW(d);
	// mlx_destroy_image(d->mlx->mlx, d->mlx->img);
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	initWindow(d);
	return(0);
}
