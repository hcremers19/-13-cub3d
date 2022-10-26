/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moovePOV.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:38:41 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/26 19:39:17 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	rotE(t_global *d)
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

void	rotW(t_global *d)
{
	double oldDirX;
	double oldScreenX;

	oldDirX = d->player->dirX;
	d->player->dirX = \
		d->player->dirX * cos(-ROT) - d->player->dirY * sin(-ROT);
	d->player->dirY = oldDirX * sin(-ROT) + d->player->dirY * cos(-ROT);
	oldScreenX = d->player->screenX;
	d->player->screenX = \
		d->player->screenX * cos(-ROT) - d->player->screenY * sin(-ROT);
    d->player->screenY = \
		oldScreenX * sin(-ROT) + d->player->screenY * cos(-ROT);
}
