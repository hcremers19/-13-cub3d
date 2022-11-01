/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moovePOV.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:38:41 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/31 17:47:25 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Change angles of the player's direction and then of screen's direction
to rotate POV to the East (left).
---------------------------------------------------------------------------- */

void	rot_e(t_global *d)
{
	double	old_dir_x;
	double	old_screen_x;

	old_dir_x = d->player->dir_x;
	d->player->dir_x = d->player->dir_x * cos((M_PI / ROT)) \
		- d->player->dir_y * sin((M_PI / ROT));
	d->player->dir_y = old_dir_x * sin((M_PI / ROT)) \
		+ d->player->dir_y * cos((M_PI / ROT));
	old_screen_x = d->player->screen_x;
	d->player->screen_x = d->player->screen_x * cos((M_PI / ROT)) \
		- d->player->screen_y * sin((M_PI / ROT));
	d->player->screen_y = old_screen_x * sin((M_PI / ROT)) \
		+ d->player->screen_y * cos((M_PI / ROT));
}

/* ----------------------------------------------------------------------------
Change angles of the player's direction and then of screen's direction
to rotate POV to the West (rigth).
---------------------------------------------------------------------------- */

void	rot_w(t_global *d)
{
	double	old_dir_x;
	double	old_screen_x;

	old_dir_x = d->player->dir_x;
	d->player->dir_x = d->player->dir_x * cos(-(M_PI / ROT)) \
		- d->player->dir_y * sin(-(M_PI / ROT));
	d->player->dir_y = old_dir_x * sin(-(M_PI / ROT)) \
		+ d->player->dir_y * cos(-(M_PI / ROT));
	old_screen_x = d->player->screen_x;
	d->player->screen_x = d->player->screen_x * cos(-(M_PI / ROT)) \
		- d->player->screen_y * sin(-(M_PI / ROT));
	d->player->screen_y = old_screen_x * sin(-(M_PI / ROT)) \
		+ d->player->screen_y * cos(-(M_PI / ROT));
}
