/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recastSage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:28:22 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/13 19:33:10 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	draw(t_global *d);
void	window_init(t_global *d);
void	my_mlx_pixel_put(t_global *d, int x, int y, int color);

//------------------------------------------------------------------
//			RECAST --> V 6:47
//------------------------------------------------------------------



//------------------------------------------------------------------
//			MAP
//------------------------------------------------------------------

int	map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,1,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void	printBlock(t_global *d, int x, int y, int color)
{
	int p;
	int k;

	k = y * H /  d->map_d->sizeY;
	while(++k < ((y + 1) * H / d->map_d->sizeY))
	{
		p = x * W / d->map_d->sizeX;
		while(++p < ((x + 1) * W / d->map_d->sizeX))
			my_mlx_pixel_put(d, p, k, color);
	}				
}

void	drawMap2D(t_global *d)
{
	int	x;
	int	y;

	y = -1;
	while(++y < d->map_d->sizeY)
	{
		x = -1;
		while(++x < d->map_d->sizeX)
		{
			if(map[y * d->map_d->sizeX + x] == 1)
				printBlock(d, x, y, 0x00FFFFFF);
			else
				printBlock(d, x, y, 0x00000000);		
		}
	}
}

//------------------------------------------------------------------
//			HOOK
//------------------------------------------------------------------

int	key_hook(int keycode, t_global *d)
{
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx_d->mlx, d->mlx_d->mlx_win);
		exit(0);// ! FREE
	}
	if (keycode == 13)					//W
	{
		d->player->posX += d->player->pdx;
		d->player->posY += d->player->pdy;
	}
	if (keycode == 0 || keycode == 123)	//A && left
	{
		d->player->alpha -= 0.1;
		if(d->player->alpha < 0)
			d->player->alpha += 2 * M_PI;
		d->player->pdx = cos(d->player->alpha) * 5;
		d->player->pdy = sin(d->player->alpha) * 5;
	}
	if (keycode == 1)					//S
	{
		d->player->posX -= d->player->pdx;
		d->player->posY -= d->player->pdy;
	}
	if (keycode == 2 || keycode == 124)	//D && rigth
	{
		d->player->alpha += 0.1;
		if(d->player->alpha > 2 * M_PI)
			d->player->alpha -= 2 * M_PI;
		d->player->pdx = cos(d->player->alpha) * 5;
		d->player->pdy = sin(d->player->alpha) * 5;
	}
	mlx_clear_window(d->mlx_d->mlx, d->mlx_d->mlx_win);
	window_init(d);
	return(0);
}

//------------------------------------------------------------------
//			DRAW
//------------------------------------------------------------------

void	my_mlx_pixel_put(t_global *d, int x, int y, int color)
{
	char	*dst;

	dst = d->mlx_d->addr + (y * d->mlx_d->line_len + x * (d->mlx_d->bpp / 8));
	*(unsigned int*)dst = color;
}

void	draw(t_global *d)
{
	drawMap2D(d);// plateau 2D
	my_mlx_pixel_put(d, d->player->posX, d->player->posY, 0x00FF0000);//player
	mlx_put_image_to_window(d->mlx_d->mlx, d->mlx_d->mlx_win, d->mlx_d->img, 0, 0);
}

//------------------------------------------------------------------
//			INIT
//------------------------------------------------------------------

void	window_init(t_global *d)
{
	d->mlx_d->img = mlx_new_image(d->mlx_d->mlx, W, H);
	if (!d->mlx_d->img)
		return ;
	d->mlx_d->addr = mlx_get_data_addr(d->mlx_d->img, &d->mlx_d->bpp, &d->mlx_d->line_len, &d->mlx_d->endian);
	if (!d->mlx_d->addr)
		return ;
	draw(d);
}

void	init(t_global *d)
{
	d->mlx_d->mlx = mlx_init();
	if(!d->mlx_d->mlx)
		return ;
	d->mlx_d->mlx_win = mlx_new_window(d->mlx_d->mlx, W, H, "cub3D");
	if(!d->mlx_d->mlx_win)
		return ;
	window_init(d);
	mlx_hook(d->mlx_d->mlx_win, 2, (1L << 0), &key_hook, d);// PRESS + RELEASE
	// mlx_mouse_hook(d->mlx_d->mlx_win, &mouse_hook, d);
	mlx_loop(d->mlx_d->mlx);
}

//------------------------------------------------------------------
//			MAIN
//------------------------------------------------------------------

int	main(void)
{
	t_global	*d;
	
	d = (t_global *)malloc(sizeof(t_global));
	d->player = (t_player *)malloc(sizeof(t_player));
	d->mlx_d = (t_mlx *)malloc(sizeof(t_mlx));
	d->map_d = (t_map *)malloc(sizeof(t_map));
	if(!d || !d->player || !d->mlx_d || !d->map_d)
		return(0);
	//---------------------------------------------------
	// Parsing init
	//---------------------------------------------------
	d->player->posX = 200;
	d->player->posY = 200;

	d->player->alpha = M_PI / 2; 		// = Nord

	d->player->pdx = cos(d->player->alpha) * 5;
	d->player->pdy = sin(d->player->alpha) * 5;

	// d->player->alpha = 3 * M_PI / 2; 	// = SUD
	// d->player->alpha = M_PI; 			// = W
	// d->player->alpha = 0;				// = E

	d->map_d->sizeX = 8;
	d->map_d->sizeY = 8;
	d->map_d->aera = d->map_d->sizeX * d->map_d->sizeY;

	//---------------------------------------------------
	init(d);
	return(0);
}
