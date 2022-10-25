/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initDrawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:22:41 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/25 12:56:07 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	initOneWall(t_global *d, t_wall *wall)
{
	int	fd;
	// Verif si pas deja prise
	fd = open(wall->path, O_RDONLY);
	if(fd <= 0)
		ft_exit(d, ER_OP);

	// .xpm --------------------------------
	wall->ptr = mlx_xpm_file_to_image(d->mlx->mlx, wall->path, \
		&wall->sizeX, &wall->sizeY);
	// .png --------------------------------
	// wall->ptr = mlx_png_file_to_image(d->mlx->mlx, ".png", \
		// &wall->sizeX, &dwall->sizeY);
	wall->addr = mlx_get_data_addr(wall->ptr, &wall->bpp, \
		&wall->line_len, &wall->endian);
	close(fd);
}

void	initWalls(t_global *d)
{
	initOneWall(d, d->map->wallN);
	initOneWall(d, d->map->wallS);
	initOneWall(d, d->map->wallE);
	initOneWall(d, d->map->wallW);
}

void	initDir(t_global *d)
{
	if(d->player->orientation == 'N' || d->player->orientation == 'S')
	{
		d->player->screenX = 0.6;
		d->player->screenY = 0;
		d->player->dirX = 0;
		if(d->player->orientation == 'N')
			d->player->dirY = 1;	
		else
			d->player->dirY = -1;
	}
	else if(d->player->orientation == 'E' || d->player->orientation == 'W')
	{
		d->player->screenX = 0;
		d->player->screenY = 0.6;	
		d->player->dirY = 0;
		if(d->player->orientation == 'E')
			d->player->dirX = 1;
		else
			d->player->dirX = -1;
	}
}

void	initWindow(t_global *d)
{
	d->mlx->img = mlx_new_image(d->mlx->mlx, WIGHT, HEIGHT);
	if (!d->mlx->img)
		return ;
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp, \
		&d->mlx->line_len, &d->mlx->endian);
	if (!d->mlx->addr)
		return ;
	recastLoop(d);
	// drawMap2D(d); // mini map
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->mlx_win, d->mlx->img, 0, 0);
}

void	init(t_global *d)
{
	d->mlx->mlx = mlx_init();
	if(!d->mlx->mlx)
		return ;
	d->mlx->mlx_win = mlx_new_window(d->mlx->mlx, WIGHT, HEIGHT, "cub3D");
	if(!d->mlx->mlx_win)
		return ;
	initDir(d);
	initWalls(d);
	initWindow(d);
	mlx_hook(d->mlx->mlx_win, 2, (1L << 0), &key_hook, d);
	mlx_hook(d->mlx->mlx_win, RED_CROSS, 0, &ft_exit_cross, d);
	mlx_loop(d->mlx->mlx);
}  
