/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:27:48 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/31 18:32:27 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Raycast_loop order : 7'/7.
Put a colored pixel on the screen at X and Y given positions using MLX image 
data.
---------------------------------------------------------------------------- */

void	my_mlx_pixel_put(t_global *d, int x, int y, int color)
{
	char	*dst;

	dst = d->mlx->addr + (y * d->mlx->line_len + x * (d->mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

/* ----------------------------------------------------------------------------
Raycast_loop order : 4/7.
Calcule the length between the player (POV) and the wall the dertermine 
the verticals distances between the bottom of the screen and the wall (draw_start), 
the heigth of the wall (draw_end - draw_start) and finally the distance between 
the wall and the top of the screen.
---------------------------------------------------------------------------- */

void	get_draw_lines(t_global *d)
{
	if (!d->ray->side)
		d->ray->size_ray = fabs((d->ray->map_x - d->player->pos_x + \
			(1 - d->ray->jump_x) / 2) / d->ray->raydir_x);
	else
		d->ray->size_ray = fabs((d->ray->map_y - d->player->pos_y + \
			(1 - d->ray->jump_y) / 2) / d->ray->raydir_y);
	d->ray->line_h = (int)(HEIGHT / d->ray->size_ray);
	d->ray->draw_start = (-d->ray->line_h / 2) + (HEIGHT / 2);
	if (d->ray->draw_start < 0)
		d->ray->draw_start = 0;
	d->ray->draw_end = (d->ray->line_h / 2) + (HEIGHT / 2);
	if (d->ray->draw_end >= HEIGHT)
		d->ray->draw_end = HEIGHT - 1;
}

/* ----------------------------------------------------------------------------
Raycast_loop order : 1/7.
Initiation of :
	- camera plane x-coordinate (cam_x)
	- vector directions of the ray (raydir)
	- rounded position on the map (map)
	- distance the ray has to travel to go from 1 x-side (or y) to the next 
	  x-side (delta_dist)
---------------------------------------------------------------------------- */

void	init_ray(t_global *d, int x)
{
	d->player->cam_x = 2 * x / (double)WIDTH - 1;
	d->ray->raydir_x = d->player->dir_x \
		+ d->player->screen_x * d->player->cam_x;
	d->ray->raydir_y = d->player->dir_y \
		+ d->player->screen_y * d->player->cam_x;
	d->ray->map_x = (int)d->player->pos_x;
	d->ray->map_y = (int)d->player->pos_y;
	d->ray->delta_dist_x = sqrt(1 + (d->ray->raydir_y * d->ray->raydir_y) \
		/ (d->ray->raydir_x * d->ray->raydir_x));
	d->ray->delta_dist_y = sqrt(1 + (d->ray->raydir_x * d->ray->raydir_x) \
		/ (d->ray->raydir_y * d->ray->raydir_y));
}

/* ----------------------------------------------------------------------------
Raycast_loop order : 5'/7.
Initiate textures variables depending which wall the ray has hitten.
---------------------------------------------------------------------------- */

void	init_img(t_global *d, t_wall *cur_wall)
{
	d->ray->cur_wall = cur_wall;
	d->ray->tex_w = cur_wall->size_x;
	d->ray->tex_h = cur_wall->size_y;
	d->ray->ptr = cur_wall->ptr;
}

/* ----------------------------------------------------------------------------
Raycast_loop order : 5/7.
Determine which wall and the exact position where the ray hits it.
---------------------------------------------------------------------------- */

void	init_tex(t_global *d)
{
	d->ray->tex_y = 0;
	if (!d->ray->side && d->ray->jump_x == 1)
	{
		d->ray->hitpt = \
		d->player->pos_y + d->ray->size_ray * d->ray->raydir_y;
		init_img(d, d->map->wall_w);
	}
	else if (!d->ray->side)
	{
		d->ray->hitpt = \
		d->player->pos_y + d->ray->size_ray * d->ray->raydir_y;
		init_img(d, d->map->wall_e);
	}
	else if (d->ray->jump_y == -1)
	{
		d->ray->hitpt = \
		d->player->pos_x + d->ray->size_ray * d->ray->raydir_x;
		init_img(d, d->map->wall_n);
	}
	else
	{
		d->ray->hitpt = \
		d->player->pos_x + d->ray->size_ray * d->ray->raydir_x;
		init_img(d, d->map->wall_s);
	}
}
