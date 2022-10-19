/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:05:00 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/18 23:05:55 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//'d' = DATA (partout) !


#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_map // HUGO
{
	// char	**map;
	int		sizeX;
	int		sizeY;
	int		aera;
	int		colorN;
	int		colorS;
	int		colorW;
	int		colorE;
	int		colorSky;
	int		colorFloor;
} t_map;

// lodev
typedef struct s_player
{
	// First vector
	double	posX;
	double	posY;
	// Scnd vector
	double	dirX;
	double	dirY;
	// Third vector
	double	screenX;
	double	screenY;
	// Camera x
	double	camX;
	// Ray
	double	rayDirX;
	double	rayDirY;
	double	sizeRay;
	int		mapX;
	int		mapY;
	int		jumpX;	//direction to step in x or y-direction
	int		jumpY;
	int		side;
} t_player;

// typedef struct s_ray;
// {
// 	double	rayDirX;
// 	double	rayDirY;
// 	double	sizeRay;
// 	int		mapX;
// 	int		mapY;
// 	int		jumpX;	//direction to step in x or y-direction
// 	int		jumpY;
// } t_ray;


// typedef struct s_player
// {
// 	float	posX;
// 	float	posY;
// 	float	pdx;
// 	float	pdy;
// 	float	alpha;
	
// } t_player;

typedef struct s_mlx //done
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
} t_mlx;

typedef	struct s_global // in progress
{
	t_mlx		*mlx;
	t_player	*player;
	t_map		*map;
} t_global;


#endif /* STRUCTURES_H */
