/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:06:44 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 15:47:39 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	ft_exit_int(t_global *d)
{
	mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
	ft_exit(d, EXIT_S, 0);
	return (0);
}

/* ----------------------------------------------------------------------------
Int return exit function for ESC window red cross MLX mouse hook.
---------------------------------------------------------------------------- */

void	ft_exit_destroy(t_global *d, char *str, int status)
{
	mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
	ft_exit(d, str, status);
}

/* ----------------------------------------------------------------------------
Void return exit function + destroy MLX window instance.
---------------------------------------------------------------------------- */

void	ft_exit(t_global *d, char *str, int status)
{
	if (str)
		ft_putstr_fd(str, status + 1);
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
	ft_exit1(d, status);
}

void	ft_exit1(t_global *d, int status)
{
	if (d->map)
	{
		free_walls(d);
		free_map(d);
		free(d->map);
	}
	if (d)
		free(d);
	exit(status);
}

/* ----------------------------------------------------------------------------
Free every pointer of the global data struct and exit.
---------------------------------------------------------------------------- */
