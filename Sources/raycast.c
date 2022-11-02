/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:24:31 by I-lan             #+#    #+#             */
/*   Updated: 2022/11/02 14:14:24 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	get_side_dist(t_global *d)
{
	if (d->ray->raydir_x < 0)
	{
		d->ray->jump_x = -1;
		d->ray->side_dist_x = (d->player->pos_x - d->ray->map_x) \
			* d->ray->delta_dist_x;
	}
	else
	{
		d->ray->jump_x = 1;
		d->ray->side_dist_x = (d->ray->map_x + 1.0 - d->player->pos_x) \
			* d->ray->delta_dist_x;
	}
	if (d->ray->raydir_y < 0)
	{
		d->ray->jump_y = -1;
		d->ray->side_dist_y = (d->player->pos_y - d->ray->map_y) \
			* d->ray->delta_dist_y;
	}
	else
	{
		d->ray->jump_y = 1;
		d->ray->side_dist_y = (d->ray->map_y + 1.0 - d->player->pos_y) \
			* d->ray->delta_dist_y;
	}
}

/* ----------------------------------------------------------------------------
Raycast_loop order : 2/7.
SideDistX is the distance from the ray starting position to the first side
to the left, if the ray direciton has a positive x-component the first side 
to the right is used instead.
The same goes on for the y-component, but now with the first side above or be-
low the position.
---------------------------------------------------------------------------- */

void	hit_loop(t_global *d)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (d->ray->side_dist_x < d->ray->side_dist_y)
		{
			d->ray->side_dist_x += d->ray->delta_dist_x;
			d->ray->map_x += d->ray->jump_x;
			d->ray->side = 0;
		}
		else
		{
			d->ray->side_dist_y += d->ray->delta_dist_y;
			d->ray->map_y += d->ray->jump_y;
			d->ray->side = 1;
		}
		if (d->map->matrix[d->ray->map_y][d->ray->map_x] == '1')
			hit = 1;
	}
}

/* ----------------------------------------------------------------------------
Raycast_loop order : 3/7.
SideDistX and SideDistY get incremented with delta_dist_x with every jump in 
their direction, and map_x and map_y get incremented with jump_x and jump_y 
respectively until the ray hits a wall.
---------------------------------------------------------------------------- */

void	pos_tex(t_global *d)
{
	d->ray->hitpt -= floor(d->ray->hitpt);
	d->ray->tex_x = (int)(d->ray->hitpt * (double)d->ray->tex_w);
	if (d->ray->side == 0 && d->ray->raydir_x > 0)
		d->ray->tex_x = d->ray->tex_w - d->ray->tex_x - 1;
	if (d->ray->side == 1 && d->ray->raydir_y < 0)
		d->ray->tex_x = d->ray->tex_w - d->ray->tex_x - 1;
	d->ray->step = (double)d->ray->tex_h / d->ray->line_h;
	d->ray->tex_pos = (d->ray->draw_start - HEIGHT / 2 + d->ray->line_h / 2) \
		* d->ray->step;
}

/* ----------------------------------------------------------------------------
Raycast_loop order : 6/7.
Determine texture position depending on the wall, the texture of it and the 
hitpoint.
---------------------------------------------------------------------------- */

void	draw_vert(t_global *d, int x)
{
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < d->ray->draw_start)
			color = (unsigned int)d->map->ceiling;
		else if (y < d->ray->draw_end)
		{
			d->ray->tex_y = (int)d->ray->tex_pos;
			d->ray->tex_pos += d->ray->step;
			color = *(unsigned int *)(d->ray->cur_wall->addr + \
			(d->ray->tex_y * d->ray->cur_wall->line_len + \
			d->ray->tex_x * (d->ray->cur_wall->bpp / 8)));
		}
		else
			color = (unsigned int)d->map->floor;
		my_mlx_pixel_put(d, x, y, color);
	}
}

/* ----------------------------------------------------------------------------
Raycast_loop order : 7/7.
Using "my_mlx_pixel_put" and draw distances, it determines which color of the
x-coordinate vertical stripe the y-coordinate should be. Floor, textured 
wall of ceiling.
---------------------------------------------------------------------------- */

void	raycast_loop(t_global *d)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(d, x);
		get_side_dist(d);
		hit_loop(d);
		get_draw_lines(d);
		init_tex(d);
		pos_tex(d);
		draw_vert(d, x);
		x++;
	}
}

/* ----------------------------------------------------------------------------
Main raycasting loop. Initiate, calculate and draw vertical stripes for every
x-coordinate on the screen to give the 3D impression.
---------------------------------------------------------------------------- */
