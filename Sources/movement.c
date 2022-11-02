/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:44:14 by I-lan             #+#    #+#             */
/*   Updated: 2022/11/02 14:08:53 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	move_n(t_global *d)
{
	if (d->map->matrix[(int)(d->player->pos_y + d->player->dir_y * SPEED)] \
		[(int)(d->player->pos_x)] != '1')
		d->player->pos_y += d->player->dir_y * SPEED;
	if (d->map->matrix[(int)(d->player->pos_y)][(int)(d->player->pos_x + \
		d->player->dir_x * SPEED)] != '1')
		d->player->pos_x += d->player->dir_x * SPEED;
}

/* ----------------------------------------------------------------------------
Allow the player to move FORWARD (North) if there is no wall only in that 
direction. Handle the variation of the X position and the Y position.
---------------------------------------------------------------------------- */

void	move_s(t_global *d)
{
	if (d->map->matrix[(int)(d->player->pos_y - d->player->dir_y * SPEED)] \
		[(int)(d->player->pos_x)] != '1')
		d->player->pos_y -= d->player->dir_y * SPEED;
	if (d->map->matrix[(int)(d->player->pos_y)] \
		[(int)(d->player->pos_x - d->player->dir_x * SPEED)] != '1')
		d->player->pos_x -= d->player->dir_x * SPEED;
}

/* ----------------------------------------------------------------------------
Allow the player to move BACKWARDS (South) if there is no wall only in that 
direction.
---------------------------------------------------------------------------- */

void	move_e(t_global *d)
{
	if (d->map->matrix[(int)(d->player->pos_y)] \
		[(int)(d->player->pos_x - d->player->screen_x * SPEED)] != '1')
		d->player->pos_x -= d->player->screen_x * SPEED;
	if (d->map->matrix[(int)(d->player->pos_y - d->player->screen_y * SPEED)] \
		[(int)(d->player->pos_x)] != '1')
		d->player->pos_y -= d->player->screen_y * SPEED;
}

/* ----------------------------------------------------------------------------
Allow the player to move LEFT (East) if there is no wall only in that 
direction. The player then moves to the left without changing its POV.
---------------------------------------------------------------------------- */

void	move_w(t_global *d)
{
	if (d->map->matrix[(int)(d->player->pos_y)][(int)(d->player->pos_x + \
		d->player->screen_x * SPEED)] != '1')
		d->player->pos_x += d->player->screen_x * SPEED;
	if (d->map->matrix[(int)(d->player->pos_y + d->player->screen_y * SPEED)] \
		[(int)(d->player->pos_x)] != '1')
		d->player->pos_y += d->player->screen_y * SPEED;
}

/* ----------------------------------------------------------------------------
Allow the player to move RIGHT (West) if there is no wall only in that
direction. The player then moves to the left without changing its POV.
---------------------------------------------------------------------------- */
