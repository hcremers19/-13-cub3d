/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:06:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 13:32:53 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Int return exit fonction for ESC window red cross MLX mouse hook.
---------------------------------------------------------------------------- */

int	ft_exit_int(t_global *d)
{
	mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
	ft_exit(d, EXIT_S);
	return (0);
}

/* ----------------------------------------------------------------------------
Void return exit fonction + destroy MLX window instance.
---------------------------------------------------------------------------- */

void	ft_exit_destroy(t_global *d, char *str)
{
	mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
	ft_exit(d, str);
}

/* ----------------------------------------------------------------------------
Free the all the pointeur of the global data struct and exit.
---------------------------------------------------------------------------- */

void	ft_exit(t_global *d, char *str)
{
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
	if (d->ray)
		free(d->ray);
	if (d->key)
		free(d->key);
	ft_exit1(d);
}

void	ft_exit1(t_global *d)
{
	if (d->map)
	{
		free_walls(d);
		free_map(d);
		free(d->map);
	}
	if (d)
		free(d);
	exit(0);
}
