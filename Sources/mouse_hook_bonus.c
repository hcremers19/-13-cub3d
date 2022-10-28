/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:13:42 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/28 19:18:18 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

/* ----------------------------------------------------------------------------
Fonction for hook into mouse events. X and y are position of the mouse.
Allow the programm to rotate POV of the player by fallowing the mouse
position on the sreen.
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
