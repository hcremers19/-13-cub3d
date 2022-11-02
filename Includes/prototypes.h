/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:34:48 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 15:42:39 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

//-------------------------------------------------------------
//		exit_utils.c
//-------------------------------------------------------------

void	free_map(t_global *d);
void	free_path(t_wall *wall);
void	free_walls(t_global *d);

//-------------------------------------------------------------
//		exit.c
//-------------------------------------------------------------

int		ft_exit_int(t_global *d);
void	ft_exit_destroy(t_global *d, char *str, int status);
void	ft_exit(t_global *d, char *str, int status);
void	ft_exit1(t_global *d, int status);

//-------------------------------------------------------------
//		ft_atoi.c
//-------------------------------------------------------------

int		ft_isdigit(int c);
int		ft_limits(long long n, const char *str, int s);
int		ft_atoi(const char *str);

//-------------------------------------------------------------
//		ft_split.c
//-------------------------------------------------------------

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		wrdnbr(t_global *d, char const *s, char c);
char	**ft_clean(char **s, int i);
char	**ft_split2(char const *s, char c, char **tab, unsigned int w);
char	**ft_split(t_global *d, char const *s, char c);

//-------------------------------------------------------------
//		ft_strtrim.c
//-------------------------------------------------------------

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);

//-------------------------------------------------------------
//		get_next_line1.c
//-------------------------------------------------------------

char	*ft_keepend(t_global *d, char *str);
char	*ft_keepstart(t_global *d, char *str);
char	*sub_gnl(t_global *d, char **stat);
char	*get_next_line(t_global *d, int fd);

//-------------------------------------------------------------
//		get_next_line2.c
//-------------------------------------------------------------

void	ft_free_two_exit(t_global *d, char **s1, char **s2, char *str);
void	ft_free(char **ptr);
char	*ft_calloc(int count, int size);
char	*ft_strjoin(char *s1, char *s2);
int		ft_srch_nl(const char *str);

//-------------------------------------------------------------
//		hoock.c
//-------------------------------------------------------------

int		key_hook_press(int keycode, t_global *d);
int		key_hook_release(int keycode, t_global *d);
int		key_hook(t_global *d);

//-------------------------------------------------------------
//		initDrawing.c
//-------------------------------------------------------------

void	init_dir1(t_global *d);
void	init_dir(t_global *d);
void	init_window(t_global *d);
void	init(t_global *d);

//-------------------------------------------------------------
//		initWalls.c
//-------------------------------------------------------------

void	init_one_wall(t_global *d, t_wall *wall);
void	init_walls(t_global *d);
void	null_walls(t_global *d);

//-------------------------------------------------------------
//		libft1.c
//-------------------------------------------------------------

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putintmin(int fd);
void	ft_putnbr_fd(int n, int fd);

//-------------------------------------------------------------
//		libft2.c
//-------------------------------------------------------------

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *src);

//-------------------------------------------------------------
//		malloc.c
//-------------------------------------------------------------

void	wall_struct_malloc(t_global *d);
void	struct_malloc(t_global *d);
void	init_struct(t_global *d);

//-------------------------------------------------------------
//		moovePOV.c
//-------------------------------------------------------------

void	rot_e(t_global *d);
void	rot_w(t_global *d);

//-------------------------------------------------------------
//		mouse_hoock_bonus.c
//-------------------------------------------------------------

int		mouse_hook(int x, int y, t_global *d);

//-------------------------------------------------------------
//		mouvement.c
//-------------------------------------------------------------

void	move_n(t_global *d);
void	move_e(t_global *d);
void	move_s(t_global *d);
void	move_w(t_global *d);

//-------------------------------------------------------------
//		raycast_utils.c
//-------------------------------------------------------------

void	my_mlx_pixel_put(t_global *d, int x, int y, int color);
void	get_draw_lines(t_global *d);
void	init_ray(t_global *d, int x);
void	init_img(t_global *d, t_wall *cur_wall);
void	init_tex(t_global *d);

//-------------------------------------------------------------
//		raycast.c
//-------------------------------------------------------------

void	get_side_dist(t_global *d);
void	hit_loop(t_global *d);
void	pos_tex(t_global *d);
void	draw_vert(t_global *d, int x);
void	raycast_loop(t_global *d);

//-------------------------------------------------------------
//		read_config1.c
//-------------------------------------------------------------

void	init_flags(t_global *d);
int		open_fd(t_global *d, char *file);
void	read_config2(t_global *d);
void	read_config1(t_global *d, char *file);

//-------------------------------------------------------------
//		read_config2.c
//-------------------------------------------------------------

int		init_color2(t_global *d, char *line);
void	init_color1(t_global *d, char *line, char flag);
void	export_path(t_global *d, char **str, char *path, int *flag);
void	init_files(t_global *d, char *line, char flag);

//-------------------------------------------------------------
//		read_map1.c
//-------------------------------------------------------------

void	alloc_map(t_global *d);
void	get_dimensions2(t_global *d, char *line, int fd);
void	get_dimensions1(t_global *d, char *file);
void	read_map(t_global *d, char *file);

//-------------------------------------------------------------
//		read_map2.c
//-------------------------------------------------------------

void	valid_map(t_global *d);
void	valid_char(t_global *d, char *line, int x, int y);
void	fill_matrix2(t_global *d, char *line, int fd);
void	fill_matrix1(t_global *d, char *file);

//-------------------------------------------------------------

#endif /* PROTOTYPES_H */