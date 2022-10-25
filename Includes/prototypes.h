/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:34:48 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/25 13:04:46 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

//-------------------------------------------------------------
//	Hugo
//-------------------------------------------------------------

char	*ft_strdup(char *src);
char	*ft_strnstr(const char *haystack, const char *needle, int n);
char	*ft_strtrim(const char *s1, const char *set);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
// void	ft_error(char *error);
void	read_config(t_global *d, char *file);
void	read_map(t_global *d, char *file, int lines);

// Juste pour les tests
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *str, int fd);

//-------------------------------------------------------------
//	Key_hook
//-------------------------------------------------------------

void	mooveN(t_global *d);
void	mooveE(t_global *d);
// void	mooveS(t_global *d);
// void	mooveW(t_global *d);
void	rotE(t_global *d);
void	rotW(t_global *d);
int		key_hook(int keycode, t_global *d);

//-------------------------------------------------------------
//	Draw
//-------------------------------------------------------------

void	getSideDist(t_global *d);
void	hitLoop(t_global *d);
void	posTex(t_global *d);
void	drawVert(t_global *d, int x);
void	recastLoop(t_global *d);

//-------------------------------------------------------------
//	Recast_utils
//-------------------------------------------------------------

void	my_mlx_pixel_put(t_global *d, int x, int y, int color);
void	getDrawLines(t_global *d);
void	initRay(t_global *d, int x);
void	initImg(t_global *d, t_wall *curWall);
void	initTex(t_global *d);

//-------------------------------------------------------------
//	Mini_map_bonus
//-------------------------------------------------------------

void	printBlock(t_global *d, int x, int y, int color);
void	drawMap2D(t_global *d);

//-------------------------------------------------------------
//	InitDrawing
//-------------------------------------------------------------

void	initOneWall(t_global *d, t_wall *wall);
void	initWalls(t_global *d);
void	initDir(t_global *d);
void	initWindow(t_global *d);
void	init(t_global *d);

//-------------------------------------------------------------
//	Utils
//-------------------------------------------------------------

// int		ft_strlen(char *str);

//-------------------------------------------------------------
//	Exit
//-------------------------------------------------------------

int		ft_exit_cross(t_global *d);
void	freeWalls(t_global *d);
void	ft_exit(t_global *d, char *str);

//-------------------------------------------------------------
//	Malloc
//-------------------------------------------------------------

void	wallStructMalloc(t_global *d);
void	structMalloc(t_global *d);

//-------------------------------------------------------------

#endif /* PROTOTYPES_H */