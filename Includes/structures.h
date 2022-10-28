/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:05:00 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/28 10:41:28 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_map	t_map;
typedef struct s_ray	t_ray;
typedef struct s_mlx	t_mlx;
typedef struct s_wall	t_wall;
typedef struct s_flags	t_flags;
typedef struct s_player	t_player;
typedef struct s_key	t_key;
typedef struct s_global	t_global;

struct s_wall
{
	char	*path;
	void	*ptr;
	void	*addr;
	int		line_len;
	int		bpp;
	int		endian;	
	int		size_x;
	int		size_y;
};

struct s_map
{
	char			**matrix;
	int				map_height;
	int				map_width;
	unsigned int	floor;
	unsigned int	ceiling;
	t_wall			*wall_n;
	t_wall			*wall_s;
	t_wall			*wall_e;
	t_wall			*wall_w;
};

struct s_player
{
	char	orientation;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	screen_x;
	double	screen_y;
	double	cam_x;
};

struct s_ray
{
	double	raydir_x;
	double	raydir_y;
	double	size_ray;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	hitpt;
	double	step;
	double	tex_pos;
	int		map_x;
	int		map_y;
	int		jump_x;
	int		jump_y;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
	int		tex_h;
	int		tex_w;
	void	*ptr;
	t_wall	*cur_wall;
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
	int		no;
	int		so;
	int		ea;
	int		we;
	int		f;
	int		c;
	int		lines;
	int		players;
};

struct s_key
{
	int		kw;
	int		ks;
	int		ka;
	int		kd;
	int		kleft;
	int		kright;
};

struct s_global
{
	t_flags		*flags;
	t_mlx		*mlx;
	t_player	*player;
	t_ray		*ray;
	t_map		*map;
	t_key		*key;
};

#endif /* STRUCTURES_H */
