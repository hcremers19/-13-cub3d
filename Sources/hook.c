/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:57:26 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/26 19:44:28 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	key_hook(int keycode, t_global *d)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
		ft_exit(d, EXIT_S);
	}
	if (keycode == W)
		mooveN(d);
	if (keycode == S)
		mooveS(d);
	if(keycode == A)
		mooveE(d);  
	if(keycode == D)
		mooveW(d);
	if (keycode == RIGHT_ARR)
		rotE(d);
	if (keycode == LEFT_ARR)
		rotW(d);
	// Laquelle est mieux ?
	mlx_destroy_image(d->mlx->mlx, d->mlx->img);
	// mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	initWindow(d);
	return(0);
}
