/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initDrawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:41 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/27 16:17:49 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	init_dir1(t_global *d)
{
	if (d->player->orientation == 'W')
	{
		d->player->dir_x = 1.0;
		d->player->dir_y = 0.0;
		d->player->screen_x = 0.0;
		d->player->screen_y = 1.0;
	}
	else if (d->player->orientation == 'E')
	{
		d->player->dir_x = -1.0;
		d->player->dir_y = 0.0;
		d->player->screen_x = 0.0;
		d->player->screen_y = -1.0;
	}
}

void	init_dir(t_global *d)
{
	if (d->player->orientation == 'N')
	{
		d->player->dir_x = 0.0;
		d->player->dir_y = -1.0;
		d->player->screen_x = 1.0;
		d->player->screen_y = 0.0;
	}
	else if (d->player->orientation == 'S')
	{
		d->player->dir_x = 0.0;
		d->player->dir_y = 1.0;
		d->player->screen_x = -1.0;
		d->player->screen_y = 0.0;
	}
	else
	{
		init_dir1(d);
	}
}

void	init_window(t_global *d)
{
	d->mlx->img = mlx_new_image(d->mlx->mlx, WIDTH, HEIGHT);
	if (!d->mlx->img)
		ft_exit(d, ER_MLX_IM);
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp, \
		&d->mlx->line_len, &d->mlx->endian);
	if (!d->mlx->addr)
		ft_exit(d, ER_MLX_AD);
	raycast_loop(d);
	// drawMap2D(d); // mini map
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->mlx_win, d->mlx->img, 0, 0);
}

void	init(t_global *d)
{
	d->mlx->mlx = mlx_init();
	if (!d->mlx->mlx)
		ft_exit(d, ER_MLX_IN);
	d->mlx->mlx_win = mlx_new_window(d->mlx->mlx, WIDTH, HEIGHT, "cub3D");
	if (!d->mlx->mlx_win)
		ft_exit(d, ER_MLX_IN);
	init_dir(d);
	init_walls(d);
	init_window(d);
	// mlx_hook(d->mlx->mlx_win, 2, 0, &key_hook_press, d);
	// mlx_hook(d->mlx->mlx_win, 3, 0, &key_hook_release, d);
	// mlx_hook(d->mlx->mlx_win, RED_CROSS, 0, &ft_exit_cross, d);
	// mlx_loop_hook(d->mlx->mlx, &key_hook, d);
	// mlx_loop(d->mlx->mlx);
}
