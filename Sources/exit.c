/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:06:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/26 03:33:47 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	freeWalls(t_global *d)
{
	if(d->map->wallN)
		free(d->map->wallN);
	if(d->map->wallS)
		free(d->map->wallS);
	if(d->map->wallE)
		free(d->map->wallE);
	if(d->map->wallW)
		free(d->map->wallW);
}

int		ft_exit_cross(t_global *d)
{
	ft_exit(d, EXIT_S);
	return(0);
}

void	ft_exit(t_global *d, char *str)
{
	// freeWalls(d);
	if(str)
		write(2, str, ft_strlen(str));
	if(d->flags)
		free(d->flags);
	if(d->player)
		free(d->player);
	if(d->mlx)
		free(d->mlx);
	if(d->map)
		free(d->map);
	if(d->ray)
		free(d->ray);
	if(d)
		free(d);
	exit(1);
}
