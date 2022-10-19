/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recastSage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:28:22 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/18 20:32:27 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	draw(t_global *d);
void	window_init(t_global *d);
void	my_mlx_pixel_put(t_global *d, int x, int y, int color);

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

//------------------------------------------------------------------
//			RECAST --> V 6:47
//------------------------------------------------------------------

void	drawMap3D(t_global *d, float lineO, float lineH, float r)
{
	int i = -1;
	while(++i < lineO)
	{
		my_mlx_pixel_put(d, i++, r, 0x00FF0000);
	}
	while(i < lineO + lineH)
	{
		my_mlx_pixel_put(d, i++, r, 0x00FFFF00);
	}
	while(i < lineO + lineH + lineO)
	{
		my_mlx_pixel_put(d, i++, r, 0x00FF0000);
	}
}

float	pythagor(float ax, float ay, float bx, float by)
{
	return(sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	math3D(t_global *d)
{
	int		r, mx, my, mp, dof;
	float	rx, ry, ra, x0, y0;
	float	aTan;
	float	nTan;
	float	disT;
	float	disH, hx = d->player->posX, hy = d->player->posY;
	float	disV, vx = d->player->posX, vy = d->player->posY;

	float	ca;
	float 	lineH; 
	float	lineO;

	r = -1;
	ra = d->player->alpha - (OD * 30);
	if(ra < 0)
		ra += 2* M_PI;
	else if(ra > 2 * M_PI)
		ra -= 2* M_PI;
	while(++r < 60)
	{
		//Check horizontal intersections lines
		dof = 0;
		aTan = -1 / tan(ra);
		//is the ray looking up or down?
		if(ra > M_PI)//looking up
		{
			ry = (((int)d->player->posY >> 6) << 6) - 0.0001;//y first hit
			rx = (d->player->posY - ry) * aTan + d->player->posX;//x first hit
			y0 = -64;
			x0 = -y0 * aTan;
		}
		if(ra < M_PI)//looking down
		{
			ry = (((int)d->player->posY >> 6) << 6) + 64;//y first hit
			rx = (d->player->posY - ry) * aTan + d->player->posX;//x first hit
			y0 = 64;
			x0 = -y0 * aTan;
		}
		if(ra == 0 || ra == M_PI)//looking straight left or right
		{
			rx = d->player->posX;
			ry = d->player->posY;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * d->map->sizeX + mx;
			if(mp > 0 && mp < d->map->sizeX * d->map->sizeY && map[mp] == 1)// hit a wall
			{
				hx = rx;
				hy = ry;
				disH = pythagor(d->player->posX, d->player->posY, hx, hy);
				dof = 8;
			}
			else //didn't hit a wall, looking for next horizontal line
			{
				rx += x0;
				ry += y0;
				dof += 1;
			}
		}
	//---------------------------------------------------------------
		//Check vertical intersections lines
		dof = 0;
		nTan = -tan(ra);
		if(ra > (M_PI / 2) && ra < (3 * M_PI / 2))//looking left
		{
			rx = (((int)d->player->posX >> 6) << 6) - 0.0001;//y first hit
			ry = (d->player->posX - rx) * nTan + d->player->posY;//x first hit
			x0 = -64;
			y0 = -x0 * nTan;
		}
		if(ra < (M_PI / 2) || ra > (3 * M_PI / 2))//looking right
		{
			rx = (((int)d->player->posX >> 6) << 6) + 64;//y first hit
			ry = (d->player->posX - rx) * nTan + d->player->posY;//x first hit
			x0 = 64;
			y0 = -x0 * nTan;
		}
		if(ra == 0 || ra == M_PI)//looking up or down
		{
			rx = d->player->posX;
			ry = d->player->posY;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * d->map->sizeX + mx;
			if(mp > 0 && mp < d->map->sizeX * d->map->sizeY && map[mp] == 1)
			{
				vx = rx;
				vy = ry;
				disV = pythagor(d->player->posX, d->player->posY, vx, vy);
				dof = 8;
			}
			else //didn't hit a wall, looking for next line
			{
				rx += x0;
				ry += y0;
				dof += 1;
			}
		}
		if(disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
		}
		if(disV > disH)
		{
			rx = hx;
			ry = hy;
			disT = disH;
		}
		//---------------------------------------------------------------
		// correcting fisheye
		ca = d->player->alpha - ra;
		if(ca < 0)
			ca += 2 * M_PI;
		if(ca > 2 * M_PI)
			ca -= 2 * M_PI;
		disT *= cos(ca);
		//---------------------------------------------------------------
		lineH = (d->map->aera * H) / disT;
		if (lineH > H)
			lineH = H;
		lineO = (W / 2) - (lineH / 2);

		drawMap3D(d, lineO, lineH, r);
		//---------------------------------------------------------------
		// Main while
		ra += OD;
		if(ra < 0)
			ra += 2* M_PI;
		if(ra > 2 * M_PI)
			ra -= 2* M_PI;
	}
}

//------------------------------------------------------------------
//			MAP
//------------------------------------------------------------------

void	printBlock(t_global *d, int x, int y, int color)
{
	int p;
	int k;

	k = y * H /  d->map->sizeY;
	while(++k < ((y + 1) * H / d->map->sizeY))
	{
		p = x * W / d->map->sizeX;
		while(++p < ((x + 1) * W / d->map->sizeX))
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
			if(map[y * d->map->sizeX + x] == 1)
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
		mlx_d  estroy_window(d->mlx->mlx, d->mlx->mlx_win);
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
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	window_init(d);
	return(0);
}

//------------------------------------------------------------------
//			DRAW
//------------------------------------------------------------------

void	my_mlx_pixel_put(t_global *d, int x, int y, int color)
{
	char	*dst;

	dst = d->mlx->addr + (y * d->mlx->line_len + x * (d->mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

void	draw(t_global *d)
{
	// drawMap2D(d);// plateau 2D
	math3D(d);
	// my_mlx_pixel_put(d, d->player->posX, d->player->posY, 0x00FF0000);//player
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->mlx_win, d->mlx->img, 0, 0);
}

//------------------------------------------------------------------
//			INIT
//------------------------------------------------------------------

void	window_init(t_global *d)
{
	d->mlx->img = mlx_new_image(d->mlx->mlx, W, H);
	if (!d->mlx->img)
		return ;
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp, &d->mlx->line_len, &d->mlx->endian);
	if (!d->mlx->addr)
		return ;
	draw(d);
}

void	init(t_global *d)
{
	d->mlx->mlx = mlx_init();
	if(!d->mlx->mlx)
		return ;
	d->mlx->mlx_win = mlx_new_window(d->mlx->mlx, W, H, "cub3D");
	if(!d->mlx->mlx_win)
		return ;
	window_init(d);
	mlx_hook(d->mlx->mlx_win, 2, (1L << 0), &key_hook, d);// PRESS + RELEASE
	// mlx_mouse_hook(d->mlx->mlx_win, &mouse_hook, d);
	mlx_loop(d->mlx->mlx);
}

//------------------------------------------------------------------
//			MAIN
//------------------------------------------------------------------

int	main(void)
{
	t_global	*d;
	
	d = (t_global *)malloc(sizeof(t_global));
	d->player = (t_player *)malloc(sizeof(t_player));
	d->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	d->map = (t_map *)malloc(sizeof(t_map));
	if(!d || !d->player || !d->mlx || !d->map)
		return(0);
	//---------------------------------------------------
	// Parsing init
	//---------------------------------------------------
	d->player->posX = 100;
	d->player->posY = 100;
	d->player->alpha = M_PI / 2; 			// = Nord

	d->player->pdx = cos(d->player->alpha) * 5;
	d->player->pdy = sin(d->player->alpha) * 5;

	// d->player->alpha = 3 * M_PI / 2; 	// = SUD
	// d->player->alpha = M_PI; 			// = W
	// d->player->alpha = 0;				// = E

	d->map->sizeX = 8;
	d->map->sizeY = 8;
	d->map->aera = d->map->sizeX * d->map->sizeY;

	//---------------------------------------------------
	init(d);
	return(0);
}
