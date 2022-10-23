/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:24:31 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/24 01:40:04 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

//---------------------------------------------------
// Out init
//---------------------------------------------------

int	map[10][10] =
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

//------------------------------------------------------------------
//			DRAW 3D
//------------------------------------------------------------------

void	hitLoop(t_global *d)
{
	int hit;

	hit = 0;
	while(!hit)
	{
		if(d->ray->sideDistX < d->ray->sideDistY)
		{
			d->ray->sideDistX += d->ray->deltaDistX;
			d->ray->mapX += d->ray->jumpX;
			d->ray->side = 0;
		}
		else
		{
			d->ray->sideDistY += d->ray->deltaDistY;
			d->ray->mapY += d->ray->jumpY;
			d->ray->side = 1;
		}
		if(map[d->ray->mapX][d->ray->mapY] == 1)
			hit = 1;
	}	
}

void	getSideDist(t_global *d)
{
		if(d->ray->rayDirX < 0)
		{
			d->ray->jumpX = -1;
			d->ray->sideDistX = (d->player->posX - d->ray->mapX) \
				* d->ray->deltaDistX;
		}
		else
		{
			d->ray->jumpX = 1;
			d->ray->sideDistX = (d->ray->mapX + 1.0 - d->player->posX) \
				* d->ray->deltaDistX;
		}
		if(d->ray->rayDirY < 0)
		{
			d->ray->jumpY = -1;
			d->ray->sideDistY = (d->player->posY - d->ray->mapY) \
				 * d->ray->deltaDistY;
		}
		else
		{
			d->ray->jumpY = 1;
			d->ray->sideDistY = (d->ray->mapY + 1.0 - d->player->posY) \
				* d->ray->deltaDistY;
		}
}

void	posTex(t_global *d, int lineH, int drawstart)
{
	d->ray->hitpt -= floor(d->ray->hitpt);
	d->ray->texX = (int)(d->ray->hitpt * (double)d->ray->texW);
	if (d->ray->side == 0 && d->ray->rayDirX > 0)
		d->ray->texX = d->ray->texW - d->ray->texX - 1;
	if (d->ray->side == 1 && d->ray->rayDirY < 0)
		d->ray->texX = d->ray->texW - d->ray->texX - 1;
	d->ray->step = (double)d->ray->texH / lineH;
	d->ray->texPos = (drawstart - HEIGHT / 2 + lineH / 2) * d->ray->step;
}

void	initWall(t_global *d)
{
	int	fd;
// Verif si pas deja prise
	fd = open("cat.xpm", O_RDONLY);
	if(fd <= 0)
		ft_exit(d, ER_OP);
	d->map->wallT->ptr = mlx_xpm_file_to_image(d->mlx->mlx, "cat.xpm", \
	&d->map->wallT->sizeX, &d->map->wallT->sizeY);

	d->map->wallT->addr = mlx_get_data_addr(d->map->wallT->ptr, \
	&d->map->wallT->bpp, &d->map->wallT->line_len, &d->map->wallT->endian);
	close(fd);
}

void	initImg(t_global *d, t_wall *curWall)
{
	d->ray->curWall = curWall;
	d->ray->texW = curWall->sizeX;
	d->ray->texH = curWall->sizeY;
	d->ray->ptr = curWall->ptr;
}

void	initTex(t_global *d)
{
	d->ray->texY = 0;
	if(!d->ray->side && d->ray->jumpX == 1)
	{
		d->ray->hitpt = \
		d->player->posY + d->ray->sizeRay * d->ray->rayDirY;
		initImg(d, d->map->wallT);//W
	}
	else if (!d->ray->side)
	{
		d->ray->hitpt = \
		d->player->posY + d->ray->sizeRay * d->ray->rayDirY;
		initImg(d, d->map->wallT);//E
	}
	else if(d->ray->jumpY == -1)
	{
		d->ray->hitpt = \
		d->player->posX + d->ray->sizeRay * d->ray->rayDirX;
		initImg(d, d->map->wallT);//S
	}
	else
	{
		d->ray->hitpt = \
		d->player->posX + d->ray->sizeRay * d->ray->rayDirX;
		initImg(d, d->map->wallT);//N
	}
}

void	my_mlx_pixel_put(t_global *d, int x, int y, int color)
{
	char	*dst;

	dst = d->mlx->addr + (y * d->mlx->line_len + x * (d->mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

void	drawVert(t_global *d, int x, int start, int end)
{
	int	i;
	unsigned int color;
	// int	*ptr;

	i = -1;
	while(++i < HEIGHT)
	{
		if(i < start)
			// color = (unsigned int)d->map->sky;
			color = 0x00FFFFFF;
		else if(i < end)
		{
			d->ray->texY = (int)d->ray->texPos;
			d->ray->texPos += d->ray->step;
			color = *(unsigned int *)(d->ray->curWall->addr + \
			(d->ray->texY * d->ray->curWall->line_len + \
			d->ray->texX * (d->ray->curWall->bpp / 8)));
		}
		else
			// color = (unsigned int)d->map->floor;
			color = 0x00000000;
		// ptr = d->mlx->addr + (i * d->mlx->line_len + x * (d->mlx->bpp / 8));
		// *ptr = color;
		my_mlx_pixel_put(d, x, i, color);
	}
}

void	draw3D(t_global *d)
{
	int x;
	
	x = -1;
	while(++x < WIGHT)
	{
		d->player->camX = 2 * x / (double)WIGHT - 1;
		d->ray->rayDirX = d->player->dirX + d->player->screenX * d->player->camX;
		d->ray->rayDirY = d->player->dirY + d->player->screenY * d->player->camX;

		d->ray->mapX = (int)d->player->posX;
		d->ray->mapY = (int)d->player->posY;

		d->ray->deltaDistX = sqrt(1 + (d->ray->rayDirY * d->ray->rayDirY) \
			/ (d->ray->rayDirX * d->ray->rayDirX));
		d->ray->deltaDistY = sqrt(1 + (d->ray->rayDirX * d->ray->rayDirX) \
			/ (d->ray->rayDirY * d->ray->rayDirY));
		getSideDist(d);
		hitLoop(d);
		//-------------------------------------------
		int	lineH;
		int	drawStart;
		int drawEnd;

		if(!d->ray->side)
			d->ray->sizeRay = (d->ray->sideDistX - d->ray->deltaDistX);
		else
			d->ray->sizeRay = (d->ray->sideDistY - d->ray->deltaDistY);
		lineH = (int)(HEIGHT / d->ray->sizeRay);
		drawStart = (-lineH / 2 ) + (HEIGHT / 2);
		if(drawStart < 0)
			drawStart = 0;
		drawEnd = (lineH / 2) + (HEIGHT / 2);
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		//---------------- init  line size
		initWall(d);
		initTex(d);
		posTex(d, lineH, drawStart);
		drawVert(d, x, drawStart, drawEnd);
	}
	// mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	// mlx_put_image_to_window(d->mlx->mlx, d->mlx->mlx_win, d->mlx->img, 0, 0);
}

//------------------------------------------------------------------
//			DRAW 2D
//------------------------------------------------------------------

void	printBlock(t_global *d, int x, int y, int color)
{
	int p;
	int k;

	k = y * HEIGHT /  (d->map->sizeY * (HEIGHT));
	while(++k < ((y + 1) * HEIGHT / d->map->sizeY))
	{
		p = x * WIGHT / ( d->map->sizeX * (WIGHT));
		while(++p < ((x + 1) * WIGHT / d->map->sizeX))
			my_mlx_pixel_put(d, p, k, color);
	}				
}

void	drawMap2D(t_global *d)
{
	int	x;
	int	y;

	y = -1;
	while(++y < d->map->sizeY)
	{
		x = -1;
		while(++x < d->map->sizeX)
		{
			if(map[x][y] == 1)
				printBlock(d, x, y, 0x00FFFFFF);
			else
				printBlock(d, x, y, 0x00000000);		
		}
	}
}

//------------------------------------------------------------------
//			WINDOW
//------------------------------------------------------------------

void	initDir(t_global *d)
{
	if(d->player->letter == 'N' || d->player->letter == 'S')
	{
		d->player->screenX = 0.6;
		d->player->screenY = 0;
		d->player->dirX = 0;
		if(d->player->letter == 'N')
			d->player->dirY = 1;	
		else
			d->player->dirY = -1;
	}
	else if(d->player->letter == 'E' || d->player->letter == 'W')
	{
		d->player->screenX = 0;
		d->player->screenY = 0.6;	
		d->player->dirY = 0;
		if(d->player->letter == 'E')
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
	draw3D(d);
	// drawMap2D(d); // mini map
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
	initWindow(d);
	mlx_hook(d->mlx->mlx_win, 2, (1L << 0), &key_hook, d);
	// mlx_mouse_hook(d->mlx->mlx_win, &mouse_hook, d);
	mlx_loop(d->mlx->mlx);
}  

//-------------------------------------------------------------------
//	MAIN
//-------------------------------------------------------------------

void	ft_exit(t_global *d, char *str)
{
	// free walls
	if(str)
		write(2, str, ft_strlen(str));
	if(d->player)
		free(d->player);
	if(d->mlx)
		free(d->mlx);
	if(d->map)
		free(d->map);
	if(d->ray)
		free(d->ray);
	if(d)
		free(d);
	exit(0);
}

void	wallStructMalloc(t_global *d)
{
	d->map->wallT = (t_wall *)malloc(sizeof(t_wall));
	if(!d->map->wallT)
		ft_exit(d, ER_MA);
	// d->map->wallN = (t_wall *)malloc(sizeof(t_wall));
	// if(!d->map->wallT)
	// 	ft_exit(d, ER_MA);
	// d->map->wallS = (t_wall *)malloc(sizeof(t_wall));
	// if(!d->map->wallT)
	// 	ft_exit(d, ER_MA);
	// d->map->wallE = (t_wall *)malloc(sizeof(t_wall));
	// if(!d->map->wallT)
	// 	ft_exit(d, ER_MA);
	// d->map->wallW = (t_wall *)malloc(sizeof(t_wall));
	// if(!d->map->wallT)
	// 	ft_exit(d, ER_MA);
}

void	structMalloc(t_global *d)
{
	d->player = (t_player *)malloc(sizeof(t_player));
	if(!d->player)
		ft_exit(d, ER_MA);
	d->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if(!d->mlx)
		ft_exit(d, ER_MA);
	d->map = (t_map *)malloc(sizeof(t_map));
	if(!d->map)
		ft_exit(d, ER_MA);
	d->ray = (t_ray *)malloc(sizeof(t_ray));
	if(!d->ray)
		ft_exit(d, ER_MA);
	wallStructMalloc(d);
}
