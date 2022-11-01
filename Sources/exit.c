/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:06:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/01 14:02:58 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Free the four wall structures of the map.
---------------------------------------------------------------------------- */

void	free_walls(t_global *d)
{
	if (d->map->wall_n)
		free(d->map->wall_n);
	if (d->map->wall_s)
		free(d->map->wall_s);
	if (d->map->wall_e)
		free(d->map->wall_e);
	if (d->map->wall_w)
		free(d->map->wall_w);
}

/* ----------------------------------------------------------------------------
Free the all the pointeur of the global data struct and exit.
---------------------------------------------------------------------------- */

int	ft_exit(t_global *d, char *str)
{
	free_walls(d);
	if (str)
		write(1, str, ft_strlen(str));
	if (d->flags)
		free(d->flags);
	if (d->player)
		free(d->player);
	if (d->mlx)
		free(d->mlx);
	if (d->map)
		free(d->map);
	if (d->ray)
		free(d->ray);
	if (d->key)
		free(d->key);
	if (d)
		free(d);
	exit(0);
	return (0);
}
