/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:34:48 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/21 01:50:31 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

//-------------------------------------------------------------
//	Key_hook_and_mooves
//-------------------------------------------------------------

void	mooveN(t_global *d);
void	mooveE(t_global *d);
void	mooveS(t_global *d);
void	mooveW(t_global *d);
int		key_hook(int keycode, t_global *d);

//-------------------------------------------------------------
//	Draw
//-------------------------------------------------------------

void	my_mlx_pixel_put(t_global *d, int x, int y, int color);

void	drawVert(t_global *d, int x, int y1, int y2);
// void	getDrawLines(t_global *d, int x);
void	hitLoop(t_global *d);
void	draw3D(t_global *d);

void	printBlock(t_global *d, int x, int y, int color);
void	drawMap2D(t_global *d);

//-------------------------------------------------------------
//	Init
//-------------------------------------------------------------

void	initDir(t_global *d);
void	init(t_global *d);
void	initWindow(t_global *d);

//-------------------------------------------------------------
//	Utils
//-------------------------------------------------------------

int		ft_strlen(char *str);

//-------------------------------------------------------------
//	MAIN
//-------------------------------------------------------------

void	ft_exit(t_global *d, char *str);
void	structMalloc(t_global *d);

#endif /* PROTOTYPES_H */