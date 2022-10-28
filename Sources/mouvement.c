/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:44:14 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/28 19:22:45 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Allow the player to move FORWARD (North) if there is no wall just in that 
direction. Handle the variation of the X position and the Y position.
---------------------------------------------------------------------------- */

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
Allow the player to move BACKWARDS (South) if there is no wall just in that 
direction.
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
Allow the player to move LEFT (East) if there is no wall just in that 
direction. The player then move to the left without changing its POV.
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
Allow the player to move RIGTH (West) if there is no wall just in that 
direction. The player then move to the left without changing its POV.
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
