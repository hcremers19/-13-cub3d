/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:06:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 12:31:42 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

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

/* ----------------------------------------------------------------------------
Exit fonction for ESC window red cross. 
---------------------------------------------------------------------------- */

int	ft_exit_int(t_global *d)
{
	mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
	ft_exit(d, EXIT_S);
	return (0);
}

/* ----------------------------------------------------------------------------
Free the all the pointeur of the global data struct and exit.
---------------------------------------------------------------------------- */
// free matrix when leaving after alloc_mat
// + destroy window if (mlx->mlx et mlx->mlx_win)

void	ft_exit(t_global *d, char *str)
{
	int	i;

	if (str)
		write(1, str, ft_strlen(str));
	if (d->flags)
	{
		if (d->flags->line)
			free(d->flags->line);
		free(d->flags);
	}
	if (d->player)
		free(d->player);
	if (d->mlx)
		free(d->mlx);
	if (d->map)
	{
		free_walls(d);
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
		free(d->map);
	}
	if (d->ray)
		free(d->ray);
	if (d->key)
		free(d->key);
	if (d)
		free(d);
	exit(0);
}
