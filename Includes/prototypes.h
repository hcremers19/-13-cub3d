/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:34:48 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/28 18:15:33 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

//-------------------------------------------------------------
//		Hugo
//-------------------------------------------------------------

void	init_files(t_global *d, char *line, char flag);
void	init_color1(t_global *d, char *line, char flag);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
void	read_map(t_global *d, char *file);
char	*ft_strtrim(const char *s1, const char *set);
void	fill_matrix1(t_global *d, char *file);
void	valid_map(t_global *d);
char	*ft_strdup(char *src);
char	*ft_calloc(int count, int size);
void	ft_free(char **ptr);
char	*ft_strjoin(char *s1, char *s2);
int		ft_srch_nl(const char *str);
char	**ft_split(t_global *d, char const *s, char c);
int		ft_atoi(const char *str);
void	read_config1(t_global *d, char *file);
void	ft_putstr_fd(char *str, int fd);

//-------------------------------------------------------------
//		MoovePOV
//-------------------------------------------------------------

void	rot_e(t_global *d);
void	rot_w(t_global *d);

//-------------------------------------------------------------
//		Mouvement
//-------------------------------------------------------------

void	move_n(t_global *d);
void	move_e(t_global *d);
void	move_s(t_global *d);
void	move_w(t_global *d);

//-------------------------------------------------------------
//		Hoock
//-------------------------------------------------------------

int		key_hook_press(int keycode, t_global *d);
int		key_hook_release(int keycode, t_global *d);
int		key_hook(t_global *d);

//-------------------------------------------------------------
//		Mouse hoock bonus
//-------------------------------------------------------------

int		mouse_hook(int x, int y, t_global *d);

//-------------------------------------------------------------
//		InitWalls
//-------------------------------------------------------------

void	init_one_wall(t_global *d, t_wall *wall);
void	init_walls(t_global *d);
void	null_walls(t_global *d);

//-------------------------------------------------------------
//		InitDrawing
//-------------------------------------------------------------

void	init_dir1(t_global *d);
void	init_dir(t_global *d);
void	init_window(t_global *d);
void	init(t_global *d);

//-------------------------------------------------------------
//		Draw
//-------------------------------------------------------------

void	get_side_dist(t_global *d);
void	hit_loop(t_global *d);
void	pos_tex(t_global *d);
void	draw_vert(t_global *d, int x);
void	raycast_loop(t_global *d);

//-------------------------------------------------------------
//		Recast_utils
//-------------------------------------------------------------

void	my_mlx_pixel_put(t_global *d, int x, int y, int color);
void	get_draw_lines(t_global *d);
void	init_ray(t_global *d, int x);
void	init_img(t_global *d, t_wall *cur_wall);
void	init_tex(t_global *d);

//-------------------------------------------------------------
//		Mini_map_bonus
//-------------------------------------------------------------

void	printBlock(t_global *d, int x, int y, int color);
void	drawMap2D(t_global *d);

void	draw_mini_map(t_global *d);

//-------------------------------------------------------------
//		Utils
//-------------------------------------------------------------

void	ft_free_mat(char **mat);

//-------------------------------------------------------------
//		Exit
//-------------------------------------------------------------

int		ft_exit_cross(t_global *d);
void	free_walls(t_global *d);
void	ft_exit(t_global *d, char *str);

//-------------------------------------------------------------
//		Malloc
//-------------------------------------------------------------

void	wall_struct_malloc(t_global *d);
void	struct_malloc(t_global *d);
void	init_struct(t_global *d);

//-------------------------------------------------------------

#endif /* PROTOTYPES_H */