/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initDrawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:41 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/26 04:13:06 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	initDir1(t_global *d)
{
	if(d->player->orientation == 'W')
	{
		d->player->dirX = 1.0;
		d->player->dirY = 0.0;
		d->player->screenX = 0.0;
		d->player->screenY = 1.0;
	}
	else if(d->player->orientation == 'E')
	{
		d->player->dirX = -1.0;
		d->player->dirY = 0.0;
		d->player->screenX = 0.0;
		d->player->screenY = -1.0;
	}
}

void	initDir(t_global *d)
{
	if(d->player->orientation == 'N')
	{
		d->player->dirX = 0.0;
		d->player->dirY = -1.0;
		d->player->screenX = 1.0;
		d->player->screenY = 0.0;
	}
	else if(d->player->orientation == 'S')
	{
		d->player->dirX = 0.0;
		d->player->dirY = 1.0;
		d->player->screenX = -1.0;
		d->player->screenY = 0.0;
	}
	else
	{
		initDir1(d);
	}
}

void	initWindow(t_global *d)
{
	d->mlx->img = mlx_new_image(d->mlx->mlx, WIGHT, HEIGHT);
	if (!d->mlx->img)
		ft_exit(d, ER_MLX_IM);
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp, \
		&d->mlx->line_len, &d->mlx->endian);
	if (!d->mlx->addr)
		ft_exit(d, ER_MLX_AD);
	raycastLoop(d);
	// drawMap2D(d); // mini map
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->mlx_win, d->mlx->img, 0, 0);
}

void	init(t_global *d)
{
	d->mlx->mlx = mlx_init();
	if(!d->mlx->mlx)
		ft_exit(d, ER_MLX_IN);
	d->mlx->mlx_win = mlx_new_window(d->mlx->mlx, WIGHT, HEIGHT, "cub3D");
	if(!d->mlx->mlx_win)
		ft_exit(d, ER_MLX_IN);
	initDir(d);
	initWalls(d);
	initWindow(d);
	mlx_hook(d->mlx->mlx_win, 2, (1L << 0), &key_hook, d);
	mlx_hook(d->mlx->mlx_win, RED_CROSS, 0, &ft_exit_cross, d);
	mlx_loop(d->mlx->mlx);
}  
