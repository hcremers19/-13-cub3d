/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:44:14 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/26 19:44:25 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	mooveN(t_global *d)
{
	if (d->map->matrix[(int)(d->player->posY + d->player->dirY * SPEED)]\
		[(int)(d->player->posX)] != '1')
		d->player->posY += d->player->dirY * SPEED;
	if (d->map->matrix[(int)(d->player->posY)][(int)(d->player->posX + \
		d->player->dirX * SPEED)] != '1')
		d->player->posX += d->player->dirX * SPEED;
}

void	mooveS(t_global *d)
{
	if (d->map->matrix[(int)(d->player->posY - d->player->dirY * SPEED)]\
		[(int)(d->player->posX)] != '1')
		d->player->posY -= d->player->dirY * SPEED;

	if (d->map->matrix[(int)(d->player->posY)]\
		[(int)(d->player->posX - d->player->dirX * SPEED)] != '1')
		d->player->posX -= d->player->dirX * SPEED;
}

void	mooveE(t_global *d)
{
	if (d->map->matrix[(int)(d->player->posY)]\
		[(int)(d->player->posX - d->player->screenX * SPEED)] != '1')
		d->player->posX -= d->player->screenX * SPEED;
	if (d->map->matrix[(int)(d->player->posY - d->player->screenY * SPEED)]\
		[(int)(d->player->posX)] != '1')
		d->player->posY -= d->player->screenY * SPEED;
}

void	mooveW(t_global *d)
{
	if (d->map->matrix[(int)(d->player->posY)][(int)(d->player->posX + \
		d->player->screenX * SPEED)] != '1')
		d->player->posX += d->player->screenX * SPEED;
	if (d->map->matrix[(int)(d->player->posY + d->player->screenY * SPEED)]\
		[(int)(d->player->posX)] != '1')
		d->player->posY += d->player->screenY * SPEED;
}
