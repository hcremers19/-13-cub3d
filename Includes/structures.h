/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:05:00 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/24 01:25:14 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_mlx	t_mlx;
typedef struct s_wall	t_wall;
typedef struct s_global	t_global;

struct s_wall
{
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
	// char	**map;
	int			 sizeX;
	int			 sizeY;
	unsigned int floor;
	unsigned int sky;
	t_wall		 *wallT;
	// t_wall	 wallN;
	// t_wall	 wallS;
	// t_wall	 wallE;
	// t_wall	 wallW;
};

struct s_player
{
	char	letter;
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

struct s_global
{
	t_mlx		*mlx;
	t_player	*player;
	t_ray		*ray;
	t_map		*map;
};


#endif /* STRUCTURES_H */
