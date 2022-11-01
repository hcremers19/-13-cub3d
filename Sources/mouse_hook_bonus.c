/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:13:42 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/31 17:47:59 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Fonction for hook into mouse events. X and y are position of the mouse.
Allow the programm to rotate POV of the player by fallowing the mouse
position on the bottom of the screen.
---------------------------------------------------------------------------- */

int	mouse_hook(int x, int y, t_global *d)
{
	static int	old_x;

	old_x = WIDTH / 2;
	if (y > (4 * HEIGHT / 5) && y < HEIGHT)
	{
		if (x > 0 && x < WIDTH)
		{
			if (x > old_x)
				rot_e(d);
			else
				rot_w(d);
		}
	}
	old_x = x;
	return (0);
}
