/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:13 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/25 17:44:47 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	ft_free_mat(char **mat)
{
	int i;

	if (!mat)
		return ;
	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
	return ;
}

void	print_map(t_global *d, int **map)												// Juste pour les tests
{
	int	y;
	int	x;

	ft_putstr_fd("d->map->map_width = ", 1); ft_putnbr_fd(d->map->map_width, 1); ft_putchar_fd(10, 1);
	ft_putstr_fd("d->map->map_height = ", 1); ft_putnbr_fd(d->map->map_height, 1); ft_putchar_fd(10, 1);
	y = 0;
	while (y < d->map->map_height)
	{
		x = 0;
		while (x < d->map->map_width)
		{
			ft_putnbr_fd(map[y][x], 1);
			x++;
		}
		ft_putchar_fd(10, 1);
		y++;
	}
}

void	convertToBinary(t_global *d)
{
	int		y;
	int		x;
	int		tmp;

	tmp = d->map->map_height;
	d->map->map_height = d->map->map_width;
	d->map->map_width = tmp;

	x = -1;
	d->map->map = (int **)malloc(sizeof(int *) * d->map->map_width);
	if (!d->map->map)
		ft_exit(d, ER_MA);
	while(++x < d->map->map_width)
	{
		y = -1;
		d->map->map[x] = (int *)malloc(sizeof(int) * d->map->map_height);
		if (!d->map->map[x])
			ft_exit(d, ER_MA);
		while(++y < d->map->map_height)
		{
			if (d->map->matrix[x][y] != '1')
				d->map->map[x][y] = 0;
			else
				d->map->map[x][y] = d->map->matrix[x][y] - '0';
		}
	}
	// ft_free_mat(d->map->matrix);
	d->map->matrix = NULL;
	// print_map(d, d->map->map);
}

int	main(int ac, char **av)
{
	t_global	*d;

	d = (t_global *)malloc(sizeof(t_global));
	if (!d)
		ft_exit(d, ER_MA);
	if (ac != 2)
		ft_exit(d, "Error: arguments\n");
	structMalloc(d);
	read_config(d, av[1]);
	// printf("x = %f", d->player->posX);
	// printf("Y = %f", d->player->posY);
	// printf("OR = %c", d->player->orientation);
	ft_putstr_fd("x =", 1); ft_putnbr_fd(d->player->posX, 1); ft_putchar_fd(10, 1);
	ft_putstr_fd("y =", 1); ft_putnbr_fd(d->player->posY, 1); ft_putchar_fd(10, 1);
	ft_putstr_fd("or = ", 1); ft_putchar_fd(d->player->orientation, 1); ft_putchar_fd(10, 1);
	//----------------------------
	convertToBinary(d);
	//----------------------------
	init(d);
	return (0);
}

// To do Alan : 
//	- 1 fct initialisation NULL ptr Wall et Ray
//	- arranger mvt E et W
//	- arranger effet fish eyes
//	- verifier leaks