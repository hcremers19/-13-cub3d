/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:05:00 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/25 13:18:49 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_mlx	t_mlx;
typedef struct s_wall	t_wall;
typedef struct s_flags	t_flags;
typedef struct s_global	t_global;

struct s_wall
{
	char	*path;
	void	*ptr;
	void	*addr;
	int		line_len;
	int		bpp;
	int		endian;	
	int		sizeX;
	int		sizeY;
};

struct s_map
{
	char		 **matrix;
	int			 map_height;
	int			 map_width;
	unsigned int floor;
	unsigned int ceiling;
	t_wall	 	 *wallN;
	t_wall	 	 *wallS;
	t_wall	  	 *wallE;
	t_wall	 	 *wallW;
};

struct s_player
{
	char	orientation;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	screenX;
	double	screenY;
	double	camX;
};

struct s_ray
{
	double	rayDirX;
	double	rayDirY;
	double	sizeRay;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	hitpt;
	double	step;
	double	texPos;
	int		mapX;
	int		mapY;
	int		jumpX;
	int		jumpY;
	int		side;
	int		lineH;
	int		drawStart;
	int		drawEnd;
	int		texX;
	int		texY;
	int		texH;
	int		texW;
	void	*ptr;
	t_wall	*curWall;
};

struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
};

struct s_flags
{
	int		NO;
	int		SO;
	int		EA;
	int		WE;
	int		F;
	int		C;
	int		lines;
};

struct s_global
{
	t_flags		*flags;
	t_mlx		*mlx;
	t_player	*player;
	t_ray		*ray;
	t_map		*map;
};

#endif /* STRUCTURES_H */
