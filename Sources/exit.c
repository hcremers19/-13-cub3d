/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:06:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/27 16:09:28 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

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

int	ft_exit_cross(t_global *d)
{
	ft_exit(d, EXIT_S);
	return (0);
}

void	ft_exit(t_global *d, char *str)
{
	// free_walls(d);
	if (str)
		write(2, str, ft_strlen(str));
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
	exit(1);
}
