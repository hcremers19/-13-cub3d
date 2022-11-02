/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:17:26 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 13:34:00 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Free map matrix
---------------------------------------------------------------------------- */

void	free_map(t_global *d)
{
	int	i;

	if (d->map->matrix)
	{
		i = 0;
		while (i < d->map->map_height)
		{
			if (d->map->matrix[i])
				free(d->map->matrix[i]);
			i++;
		}
		free(d->map->matrix);
	}
}

/* ----------------------------------------------------------------------------
Free wall string path.
---------------------------------------------------------------------------- */

void	free_path(t_wall *wall)
{
	if (wall->path)
		free(wall->path);
}

/* ----------------------------------------------------------------------------
Free the four wall structures of the map.
---------------------------------------------------------------------------- */

void	free_walls(t_global *d)
{
	if (d->map->wall_n)
	{
		free_path(d->map->wall_n);
		free(d->map->wall_n);
	}
	if (d->map->wall_s)
	{
		free_path(d->map->wall_s);
		free(d->map->wall_s);
	}
	if (d->map->wall_e)
	{
		free_path(d->map->wall_e);
		free(d->map->wall_e);
	}
	if (d->map->wall_w)
	{
		free_path(d->map->wall_w);
		free(d->map->wall_w);
	}
}
