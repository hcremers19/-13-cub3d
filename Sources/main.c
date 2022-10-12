/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:13 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/12 17:24:27 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

// MLX ---------------------------------
void	window_init(t_global *d)
{
	d->mlx = mlx_init();
	if(!d->mlx)
		return ;
	d->mlx_win = mlx_new_window(d->mlx, W, H, "cub3D");
	if(!d->mlx_win)
		return ;
	d->img = mlx_new_image(d->mlx, W, H);
	if (!d->img)
		return ;
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_len, &d->endian);
	if (!d->addr)
		return ;
	// mlx_hook(d->mlx_win, 2, (1L << 0), &key_hook, d);
	// mlx_mouse_hook(d->mlx_win, &mouse_hook, d);
	mlx_loop(d->mlx);
}
//-----------------------------------------

int	main(int ac, char **av)
{
	t_global	d;
	(void)ac;
	(void)av;
	window_init(&d);
	printf("Hello World!\n");
	return (0);
}
