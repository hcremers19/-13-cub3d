/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:57:26 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/27 13:17:37 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	key_hook_press(int keycode, t_global *d)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
		ft_exit(d, EXIT_S);
	}
	if (keycode == W || keycode == UP_ARR)
		d->key->kw = 1;
	if (keycode == S || keycode == DOWN_ARR)
		d->key->ks = 1;
	if(keycode == A)
		d->key->ka = 1;
	if(keycode == D)
		d->key->kd = 1;
	if (keycode == LEFT_ARR)
		d->key->kright = 1;
	if (keycode == RIGHT_ARR)
		d->key->kleft = 1;
	return (0);
}

int	key_hook_release(int keycode, t_global *d)
{
	if (keycode == W || keycode == UP_ARR)
		d->key->kw = 0;
	if (keycode == S || keycode == DOWN_ARR)
		d->key->ks = 0;
	if(keycode == A)
		d->key->ka = 0;
	if(keycode == D)
		d->key->kd = 0;
	if (keycode == LEFT_ARR)
		d->key->kright = 0;
	if (keycode == RIGHT_ARR)
		d->key->kleft = 0;
	return (0);
}

int	key_hook(t_global *d)
{
	if (d->key->kw == 1)
		mooveN(d);
	if (d->key->ks == 1)
		mooveS(d);
	if(d->key->ka == 1)
		mooveE(d);  
	if(d->key->kd == 1)
		mooveW(d);
	if (d->key->kleft == 1)
		rotE(d);
	if (d->key->kright == 1)
		rotW(d);
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	initWindow(d);
	return(0);
}
