/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:57:26 by I-lan             #+#    #+#             */
/*   Updated: 2022/11/02 15:44:31 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	key_hook_press(int keycode, t_global *d)
{
	if (keycode == ESC)
		ft_exit_destroy(d, EXIT_S, 0);
	if (keycode == W || keycode == UP_ARR)
		d->key->kw = 1;
	if (keycode == S || keycode == DOWN_ARR)
		d->key->ks = 1;
	if (keycode == A)
		d->key->ka = 1;
	if (keycode == D)
		d->key->kd = 1;
	if (keycode == LEFT_ARR)
		d->key->kright = 1;
	if (keycode == RIGHT_ARR)
		d->key->kleft = 1;
	return (0);
}

/* ----------------------------------------------------------------------------
Set "key" flag to one when a specific key is pressed. The flag is then used in
key_hook fonction. Exit if ESC is pressed.
---------------------------------------------------------------------------- */

int	key_hook_release(int keycode, t_global *d)
{
	if (keycode == W || keycode == UP_ARR)
		d->key->kw = 0;
	if (keycode == S || keycode == DOWN_ARR)
		d->key->ks = 0;
	if (keycode == A)
		d->key->ka = 0;
	if (keycode == D)
		d->key->kd = 0;
	if (keycode == LEFT_ARR)
		d->key->kright = 0;
	if (keycode == RIGHT_ARR)
		d->key->kleft = 0;
	return (0);
}

/* ----------------------------------------------------------------------------
Set "key" flag to zero if the key button is released.
---------------------------------------------------------------------------- */

int	key_hook(t_global *d)
{
	if (d->key->kw == 1)
		move_n(d);
	if (d->key->ks == 1)
		move_s(d);
	if (d->key->ka == 1)
		move_e(d);
	if (d->key->kd == 1)
		move_w(d);
	if (d->key->kleft == 1)
		rot_e(d);
	if (d->key->kright == 1)
		rot_w(d);
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	init_window(d);
	return (0);
}

/* ----------------------------------------------------------------------------
Key hook is constantly called in a mlx_loop_hook (main). It checks if the "key"
flag is one or zero. If it is 1 it can call 4 different movements functions 
or 2 rotations of the POV functions.
---------------------------------------------------------------------------- */
