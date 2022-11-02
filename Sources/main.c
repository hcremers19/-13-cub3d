/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:13 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 14:05:00 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	main(int ac, char **av)
{
	t_global	*d;

	if (ac != 2)
	{
		ft_putstr_fd(ER_ARG, 1);
		return (0);
	}
	d = (t_global *)malloc(sizeof(t_global));
	if (!d)
	{
		ft_putstr_fd(ER_MA, 1);
		return (0);
	}
	init_struct(d);
	struct_malloc(d);
	read_config1(d, av[1]);
	init(d);
	mlx_hook(d->mlx->mlx_win, 2, 0, &key_hook_press, d);
	mlx_hook(d->mlx->mlx_win, 3, 0, &key_hook_release, d);
	mlx_hook(d->mlx->mlx_win, RED_CROSS, 0, &ft_exit_int, d);
	mlx_loop_hook(d->mlx->mlx, &key_hook, d);
	mlx_loop(d->mlx->mlx);
	return (0);
}
