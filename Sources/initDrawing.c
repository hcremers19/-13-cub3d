/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initDrawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:41 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 15:45:09 by hcremers         ###   ########.fr       */
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

/* ----------------------------------------------------------------------------
See "init_dir" below.
---------------------------------------------------------------------------- */

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

/* ----------------------------------------------------------------------------
Set the initial direction of the POV and the screen of the player depending on
the letter (N, S, E or W) found in the map. Note that the dir(x, y) is always
perpendicular to screen(x, y) of the player.
---------------------------------------------------------------------------- */

void	init_window(t_global *d)
{
	d->mlx->img = mlx_new_image(d->mlx->mlx, WIDTH, HEIGHT);
	if (!d->mlx->img)
		ft_exit_destroy(d, ER_MLX_IM, 1);
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp, \
		&d->mlx->line_len, &d->mlx->endian);
	if (!d->mlx->addr)
		ft_exit_destroy(d, ER_MLX_AD, 1);
	raycast_loop(d);
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->mlx_win, d->mlx->img, 0, 0);
}

/* ----------------------------------------------------------------------------
Initialize window image pointer and image adress pointer to print, when it is
necessary, a new image. Call "raycast_loop" to draw on the image and then
use "put_image_to_window" to put the image on the given window.
---------------------------------------------------------------------------- */

void	init(t_global *d)
{
	d->mlx->mlx = mlx_init();
	if (!d->mlx->mlx)
		ft_exit(d, ER_MLX_IN, 1);
	d->mlx->mlx_win = mlx_new_window(d->mlx->mlx, WIDTH, HEIGHT, "cub3D");
	if (!d->mlx->mlx_win)
		ft_exit(d, ER_MLX_IN, 1);
	init_dir(d);
	init_walls(d);
	init_window(d);
}

/* ----------------------------------------------------------------------------
Initialize MLX library and create a new window instance.
Initialize initial directions of the player and POV.
Initialize wall structures with their different textures.
Launch the image.
---------------------------------------------------------------------------- */
