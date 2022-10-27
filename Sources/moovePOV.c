/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moovePOV.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:38:41 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/27 16:53:05 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	rot_e(t_global *d)
{
	double	old_dir_x;
	double	old_screen_x;

	old_dir_x = d->player->dir_x;
	d->player->dir_x = \
		d->player->dir_x * cos(ROT) - d->player->dir_y * sin(ROT);
	d->player->dir_y = \
		old_dir_x * sin(ROT) + d->player->dir_y * cos(ROT);
	old_screen_x = d->player->screen_x;
	d->player->screen_x = \
		d->player->screen_x * cos(ROT) - d->player->screen_y * sin(ROT);
	d->player->screen_y = \
		old_screen_x * sin(ROT) + d->player->screen_y * cos(ROT);
}

void	rot_w(t_global *d)
{
	double	old_dir_x;
	double	old_screen_x;

	old_dir_x = d->player->dir_x;
	d->player->dir_x = \
		d->player->dir_x * cos(-ROT) - d->player->dir_y * sin(-ROT);
	d->player->dir_y = old_dir_x * sin(-ROT) + d->player->dir_y * cos(-ROT);
	old_screen_x = d->player->screen_x;
	d->player->screen_x = \
		d->player->screen_x * cos(-ROT) - d->player->screen_y * sin(-ROT);
	d->player->screen_y = \
		old_screen_x * sin(-ROT) + d->player->screen_y * cos(-ROT);
}
