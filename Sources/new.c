/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:24:31 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/18 23:10:15 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

//---------------------------------------------------
// Out init
//---------------------------------------------------

void	window_init(t_global *d);

int test_map[8][8]=
{
	{1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,1,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1},
};

//------------------------------------------------------------------
//			Libft
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
	if(x <= W / d->map->sizeX + 1 && x >= W / d->map->sizeX - 1)
		color = 0x00000000;
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
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->mlx_win, d->mlx->img, 0, 0);
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

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		double deltaDistX;
		double deltaDistY;

		deltaDistX = sqrt(1 + (d->player->rayDirY * d->player->rayDirY) / (d->player->rayDirX * d->player->rayDirX));
		deltaDistY = sqrt(1 + (d->player->rayDirX * d->player->rayDirX) / (d->player->rayDirY * d->player->rayDirY));

		if(d->player->rayDirX < 0)
		{
			d->player->jumpX = -1;
			sideDistX = (d->player->posX - d->player->mapX) * deltaDistX;
		}
		else
		{
			d->player->jumpX = 1;
			sideDistX = (d->player->mapX + 1.0 - d->player->posX) * deltaDistX;
		}
		if(d->player->rayDirY < 0)
		{
			d->player->jumpY = -1;
			sideDistY = (d->player->posY - d->player->mapY) * deltaDistY;
		}
		else
		{
			d->player->jumpY = 1;
			sideDistY = (d->player->mapY + 1.0 - d->player->posY) * deltaDistY;
		}
		// DDA
		int	 hit = 0; //was there a wall hit?
		d->player->side = 0; //of the wall

		while(!hit)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				d->player->mapX += d->player->jumpX;
				d->player->side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				d->player->mapY += d->player->jumpY;
				d->player->side = 1;
			}
			//Check if ray has hit a wall
			if(test_map[d->player->mapX][d->player->mapY] > 0)
				hit = 1;
		}
		// Len rayon
		if(!d->player->side)
			d->player->sizeRay = (sideDistX - deltaDistX);
		else
			d->player->sizeRay = (sideDistY - deltaDistY);

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
//			HOOK
//------------------------------------------------------------------

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
	if (keycode == 13)					//W
	{
		if(!test_map[(int)(d->player->posX + d->player->dirX * speed)][(int)(d->player->posY)])
			d->player->posX += d->player->dirX * speed;
		if(!test_map[(int)(d->player->posX)][(int)(d->player->posY + d->player->dirY * speed)])
			d->player->posY += d->player->dirY * speed;
	}
	if (keycode == 2 || keycode == 124)	//D && right
	{
		double oldDirX = d->player->dirX;
		d->player->dirX = d->player->dirX * cos(angle) - d->player->dirY * sin(angle);
		d->player->dirY = oldDirX * sin(angle) + d->player->dirY * cos(angle);
		
		double oldScreenX = d->player->screenX;
		d->player->screenX = d->player->screenX * cos(angle) - d->player->screenY * sin(angle);
      	d->player->screenY = oldScreenX * sin(angle) + d->player->screenY * cos(angle);
	}
	if (keycode == 1)					//S
	{
		if(!test_map[(int)(d->player->posX - d->player->dirX * speed)][(int)(d->player->posY)])
			d->player->posX -= d->player->dirX * speed;
		if(!test_map[(int)(d->player->posX)][(int)(d->player->posY + d->player->dirY * speed)])
			d->player->posY -= d->player->dirY * speed;
	}
	if (keycode == 0 || keycode == 123)	//A && left
	{
		double oldDirX = d->player->dirX;
		d->player->dirX = d->player->dirX * cos(-angle) - d->player->dirY * sin(-angle);
		d->player->dirY = oldDirX * sin(-angle) + d->player->dirY * cos(-angle);
		
		double oldScreenX = d->player->screenX;
		d->player->screenX = d->player->screenX * cos(-angle) - d->player->screenY * sin(-angle);
      	d->player->screenY = oldScreenX * sin(-angle) + d->player->screenY * cos(-angle);
	}
	mlx_clear_window(d->mlx->mlx, d->mlx->mlx_win);
	window_init(d);
	return(0);
}

//------------------------------------------------------------------
//			WINDOW
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
	
	char c;
	c = 'E';
	if(c == 'N' || c == 'S')
	{
		d->player->screenX = 0.6;
		d->player->screenY = 0;
		if(c == 'N')
		{
			d->player->dirX = 0;
			d->player->dirY = 1;	
		}
		else
		{
			d->player->dirX = 0;
			d->player->dirY = -1;
		}
	}
	else if(c == 'E' || c == 'W')
	{
		d->player->screenX = 0;
		d->player->screenY = 0.6;	
		if(c == 'E')
		{
			d->player->dirX = 1;
			d->player->dirY = 0;
		}
		else
		{
			d->player->dirX = -1;
			d->player->dirY = 0;
		}
	}

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
