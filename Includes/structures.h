/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:05:00 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/13 19:03:02 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//'d' = DATA (partout) !


#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_map // HUGO
{
	char	**map;
	int		sizeX;
	int		sizeY;
	int		aera;
} t_map;

typedef struct s_player // Alan
{
	float	posX;
	float	posY;
	float	pdx;
	float	pdy;
	float	alpha;
	
} t_player;

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
	t_mlx		*mlx_d;
	t_player	*player;
	t_map		*map_d;
} t_global;


#endif /* STRUCTURES_H */

// lodev
// typedef struct s_player
// {
// 	double	posX;
// 	double	posY;
// 	double	screenX;
// 	double	screenY;
// 	double	pDirX;
// 	double	pDirY;
// }		t_player;