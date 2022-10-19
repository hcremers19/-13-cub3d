/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:24:31 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/19 17:33:53 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

//---------------------------------------------------
// Out init
//---------------------------------------------------

void	initWindow(t_global *d);

int test_map[8][8]=
{
	{1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,1,1,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1},
};

//------------------------------------------------------------------
//			Utils
//------------------------------------------------------------------

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str && str[i])
		i++;
	return(i);
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

void	drawVert(t_global *d, int x, int y1, int y2)
{
	int y;
	int color;

	color = 0x00FF0000;
	// if(x <= W / d->map->sizeX + 1 && x >= W / d->map->sizeX - 1)
	// 	color = 0x00000000;
	if(d->player->side == 1) //give x and y sides different brightness
		color = color / 2;
	if(y2 < y1)
  	{
		y1 += y2;
		y2 = y1 - y2;
		y1 -= y2;
	}
	if(y2 < 0 || y1 >= H  || x < 0 || x >= W)
		return ;
	if(y1 < 0) 
		y1 = 0;
	if(y2 >= W)
		y2 = H - 1;
	y = y1 - 1;
	while(++y <= y2)
		my_mlx_pixel_put(d, x, y, color);
}

void	draw(t_global *d)
{
	int x;
	
	x = -1;
	while(++x < W)
	{
		//calculate ray position and direction
		d->player->camX = 2 * x / (double)W - 1;

		d->player->rayDirX = d->player->dirX + d->player->screenX * d->player->camX;
		d->player->rayDirY = d->player->dirY + d->player->screenY * d->player->camX;
		
		//which box of the map we're in
		d->player->mapX = (int)d->player->posX;
		d->player->mapY = (int)d->player->posY;

		d->player->deltaDistX = sqrt(1 + (d->player->rayDirY * d->player->rayDirY) / (d->player->rayDirX * d->player->rayDirX));
		d->player->deltaDistY = sqrt(1 + (d->player->rayDirX * d->player->rayDirX) / (d->player->rayDirY * d->player->rayDirY));

		if(d->player->rayDirX < 0)
		{
			d->player->jumpX = -1;
			d->player->sideDistX = (d->player->posX - d->player->mapX) * d->player->deltaDistX;
		}
		else
		{
			d->player->jumpX = 1;
			d->player->sideDistX = (d->player->mapX + 1.0 - d->player->posX) * d->player->deltaDistX;
		}
		if(d->player->rayDirY < 0)
		{
			d->player->jumpY = -1;
			d->player->sideDistY = (d->player->posY - d->player->mapY) * d->player->deltaDistY;
		}
		else
		{
			d->player->jumpY = 1;
			d->player->sideDistY = (d->player->mapY + 1.0 - d->player->posY) * d->player->deltaDistY;
		}
		d->player->hit = 0; //was there a wall d->player->hit?
		d->player->side = 0; //of the wall

		while(!d->player->hit)
		{
			if(d->player->sideDistX < d->player->sideDistY)
			{
				d->player->sideDistX += d->player->deltaDistX;
				d->player->mapX += d->player->jumpX;
				d->player->side = 0;
			}
			else
			{
				d->player->sideDistY += d->player->deltaDistY;
				d->player->mapY += d->player->jumpY;
				d->player->side = 1;
			}
			if(test_map[d->player->mapX][d->player->mapY] > 0) // hit
				d->player->hit = 1;
		}
		// Len rayon
		if(!d->player->side)
			d->player->sizeRay = (d->player->sideDistX - d->player->deltaDistX);
		else
			d->player->sizeRay = (d->player->sideDistY - d->player->deltaDistY);

		// 3D Draw
		int lineH = (int)(H / d->player->sizeRay);//conversion pixels
		int drawStart = (-lineH / 2 ) + (H / 2);// here put multiplcater raise walls hight

		if(drawStart < 0)
			drawStart = 0;
		
		int drawEnd = (lineH / 2) + (H / 2);
		if(drawEnd >= H)
			drawEnd = H - 1;
		drawVert(d, x, drawStart, drawEnd);
	}
}

//------------------------------------------------------------------
//			DRAW MINIMAP
//------------------------------------------------------------------

void	printBlock(t_global *d, int x, int y, int color)
{
	int p;
	int k;

	k = y * H /  (d->map->sizeY * (H));
	while(++k < ((y + 1) * H / d->map->sizeY))
	{
		p = x * W / ( d->map->sizeX * (W));
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
			if(test_map[x][y] == 1)
				printBlock(d, x, y, 0x00FFFFFF);
			else
				printBlock(d, x, y, 0x00000000);		
		}
	}
}

//------------------------------------------------------------------
//			HOOK
//------------------------------------------------------------------

void	mooveN(t_global *d, double speed)
{
	if(!test_map[(int)(d->player->posX + d->player->dirX * speed)][(int)(d->player->posY)])
		d->player->posX += d->player->dirX * speed;
	if(!test_map[(int)(d->player->posX)][(int)(d->player->posY + d->player->dirY * speed)])
		d->player->posY += d->player->dirY * speed;
}

void	mooveE(t_global *d, double angle)
{
	double oldDirX;
	double oldScreenX;

	oldDirX = d->player->dirX;
	d->player->dirX = d->player->dirX * cos(angle) - d->player->dirY * sin(angle);
	d->player->dirY = oldDirX * sin(angle) + d->player->dirY * cos(angle);
		
	oldScreenX = d->player->screenX;
	d->player->screenX = d->player->screenX * cos(angle) - d->player->screenY * sin(angle);
    d->player->screenY = oldScreenX * sin(angle) + d->player->screenY * cos(angle);
}

void	mooveS(t_global *d, double speed)
{
	if(!test_map[(int)(d->player->posX - d->player->dirX * speed)][(int)(d->player->posY)])
		d->player->posX -= d->player->dirX * speed;
	if(!test_map[(int)(d->player->posX)][(int)(d->player->posY + d->player->dirY * speed)])
		d->player->posY -= d->player->dirY * speed;
}

void	mooveW(t_global *d, double angle)
{
	double oldDirX;
	double oldScreenX;

	oldDirX = d->player->dirX;
	d->player->dirX = d->player->dirX * cos(-angle) - d->player->dirY * sin(-angle);
	d->player->dirY = oldDirX * sin(-angle) + d->player->dirY * cos(-angle);
		
	oldScreenX = d->player->screenX;
	d->player->screenX = d->player->screenX * cos(-angle) - d->player->screenY * sin(-angle);
    d->player->screenY = oldScreenX * sin(-angle) + d->player->screenY * cos(-angle);
}

int	key_hook(int keycode, t_global *d)
{
	double	speed;
	double	angle;

	speed = 0.33;
	angle = M_PI / 12;
	if (keycode == 53)
	{
		mlx_destroy_window(d->mlx->mlx, d->mlx->mlx_win);
		exit(0);// ! FREE
	}
	if (keycode == 13) // W
		mooveN(d, speed);
	if (keycode == 2 || keycode == 124)	//D && right
		mooveE(d, angle);
	if (keycode == 1) // S
		mooveS(d, speed);
	if (keycode == 0 || keycode == 123)	//A && left
		mooveW(d, angle);
	mlx_destroy_image(d->mlx->mlx, d->mlx->img);
	initWindow(d);
	return(0);
}

//------------------------------------------------------------------
//			WINDOW
//------------------------------------------------------------------

void	initDir(t_global *d, char c)
{
	if(c == 'N' || c == 'S')
	{
		d->player->screenX = 0.6;
		d->player->screenY = 0;
		d->player->dirX = 0;
		if(c == 'N')
			d->player->dirY = 1;	
		else
			d->player->dirY = -1;
	}
	else if(c == 'E' || c == 'W')
	{
		d->player->screenX = 0;
		d->player->screenY = 0.6;	
		d->player->dirY = 0;
		if(c == 'E')
			d->player->dirX = 1;
		else
			d->player->dirX = -1;
	}
}

void	initWindow(t_global *d)
{
	d->mlx->img = mlx_new_image(d->mlx->mlx, W, H);
	if (!d->mlx->img)
		return ;
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp, &d->mlx->line_len, &d->mlx->endian);
	if (!d->mlx->addr)
		return ;
	draw(d);
	// drawMap2D(d); // mini map
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->mlx_win, d->mlx->img, 0, 0);
}

void	init(t_global *d)
{
	d->mlx->mlx = mlx_init();
	if(!d->mlx->mlx)
		return ;
	d->mlx->mlx_win = mlx_new_window(d->mlx->mlx, W, H, "cub3D");
	if(!d->mlx->mlx_win)
		return ;
	char c = 'E';// parsing
	initDir(d, c);
	initWindow(d);
	mlx_hook(d->mlx->mlx_win, 2, (1L << 0), &key_hook, d);
	// mlx_mouse_hook(d->mlx->mlx_win, &mouse_hook, d);
	mlx_loop(d->mlx->mlx);
}  

//-------------------------------------------------------------------

void	ft_free(t_global *d, char *str)
{
	if(str)
		write(2, str, ft_strlen(str));
	if(d->player)
		free(d->player);
	if(d->mlx)
		free(d->mlx);
	if(d->map)
		free(d->map);
	if(d)
		free(d);
	exit(0);
}

void	structMalloc(t_global *d)
{
	d->player = (t_player *)malloc(sizeof(t_player));
	if(!d->player)
		ft_free(d, ER_MA);
	d->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if(!d->mlx)
		ft_free(d, ER_MA);
	d->map = (t_map *)malloc(sizeof(t_map));
	if(!d->map)
		ft_free(d, ER_MA);
}

int main(void)
{
	t_global	*d = NULL;

	d = (t_global *)malloc(sizeof(t_global));
	if (!d)
		ft_free(d, ER_MA);
	structMalloc(d);
	//---------------------------------------------------
	// Parsing init
	//---------------------------------------------------
	// d->map->map = test_map;

	d->map->sizeX = 8;
	d->map->sizeX = 8;

	d->player->posX = 4; 
	d->player->posY = 4;  

	d->map->colorN = 0x00FF0000;
	d->map->colorS = 0x00FF0000;
	d->map->colorW = 0x00FF0000;
	d->map->colorE = 0x00FF0000;
	d->map->colorSky = 0x0000FF;
	d->map->colorFloor = 0x00000000;

	//---------------------------------------------------
	init(d);
	return(0);
}
