/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:17:38 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/25 12:49:06 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	wallStructMalloc(t_global *d)
{
	d->map->wallN = (t_wall *)malloc(sizeof(t_wall));
	if(!d->map->wallN)
		ft_exit(d, ER_MA);
	d->map->wallS = (t_wall *)malloc(sizeof(t_wall));
	if(!d->map->wallS)
		ft_exit(d, ER_MA);
	d->map->wallE = (t_wall *)malloc(sizeof(t_wall));
	if(!d->map->wallE)
		ft_exit(d, ER_MA);
	d->map->wallW = (t_wall *)malloc(sizeof(t_wall));
	if(!d->map->wallW)
		ft_exit(d, ER_MA);
}

void	structMalloc(t_global *d)
{
	d->flags = (t_flags *)malloc(sizeof(t_flags));
	if(!d->flags)
		ft_exit(d, ER_MA);
	d->player = (t_player *)malloc(sizeof(t_player));
	if(!d->player)
		ft_exit(d, ER_MA);
	d->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if(!d->mlx)
		ft_exit(d, ER_MA);
	d->map = (t_map *)malloc(sizeof(t_map));
	if(!d->map)
		ft_exit(d, ER_MA);
	d->ray = (t_ray *)malloc(sizeof(t_ray));
	if(!d->ray)
		ft_exit(d, ER_MA);
	wallStructMalloc(d);
}
