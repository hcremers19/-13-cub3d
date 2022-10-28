/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:13 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/28 18:01:42 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	main(int ac, char **av)
{
	t_global	*d;

	d = (t_global *)malloc(sizeof(t_global));
	if (!d)
	{
		ft_putstr_fd(ER_MA, 1);
		return (0);
	}
	init_struct(d);
	if (ac != 2)
		ft_exit(d, ER_ARG);
	struct_malloc(d);
	read_config(d, av[1]);
	init(d);
	// -----------------
	mlx_hook(d->mlx->mlx_win, 2, 0, &key_hook_press, d);
	mlx_hook(d->mlx->mlx_win, 3, 0, &key_hook_release, d);
	mlx_hook(d->mlx->mlx_win, RED_CROSS, 0, &ft_exit_cross, d);
	// BONUS
	mlx_hook(d->mlx->mlx_win, 6, 0, &mouse_hook, d);
	//------
	mlx_loop_hook(d->mlx->mlx, &key_hook, d);
	mlx_loop(d->mlx->mlx);
	// -----------------
	return (0);
}

// To do
//	- mini map
//	- verifier leaks
//  - creer/github des maps
//	- commentaires ?