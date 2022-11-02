/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:17:38 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 02:25:34 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Memory allocation of the 4 wall structure of the map.
---------------------------------------------------------------------------- */

void	wall_struct_malloc(t_global *d)
{
	d->map->wall_n = (t_wall *)malloc(sizeof(t_wall));
	if (!d->map->wall_n)
		ft_exit(d, ER_MA);
	d->map->wall_n->path = NULL;
	d->map->wall_s = (t_wall *)malloc(sizeof(t_wall));
	if (!d->map->wall_s)
		ft_exit(d, ER_MA);
	d->map->wall_s->path = NULL;
	d->map->wall_e = (t_wall *)malloc(sizeof(t_wall));
	if (!d->map->wall_e)
		ft_exit(d, ER_MA);
	d->map->wall_e->path = NULL;
	d->map->wall_w = (t_wall *)malloc(sizeof(t_wall));
	if (!d->map->wall_w)
		ft_exit(d, ER_MA);
	d->map->wall_w->path = NULL;
}

/* ----------------------------------------------------------------------------
Memory allocation of all pointeurs of t_glabal data struct.
---------------------------------------------------------------------------- */

void	struct_malloc(t_global *d)
{
	d->flags = (t_flags *)malloc(sizeof(t_flags));
	if (!d->flags)
		ft_exit(d, ER_MA);
	d->flags->line = NULL;
	d->player = (t_player *)malloc(sizeof(t_player));
	if (!d->player)
		ft_exit(d, ER_MA);
	d->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!d->mlx)
		ft_exit(d, ER_MA);
	d->map = (t_map *)malloc(sizeof(t_map));
	if (!d->map)
		ft_exit(d, ER_MA);
	null_walls(d);
	d->map->matrix = NULL;
	d->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!d->ray)
		ft_exit(d, ER_MA);
	d->key = (t_key *)malloc(sizeof(t_key));
	if (!d->key)
		ft_exit(d, ER_MA);
	wall_struct_malloc(d);
}

/* ----------------------------------------------------------------------------
Set initially all of global data struct pointeurs to NULL to simplificate free.
---------------------------------------------------------------------------- */

void	init_struct(t_global *d)
{
	d->flags = NULL;
	d->player = NULL;
	d->mlx = NULL;
	d->map = NULL;
	d->ray = NULL;
	d->key = NULL;
}
