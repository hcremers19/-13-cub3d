/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:22:06 by acaillea          #+#    #+#             */
/*   Updated: 2022/11/02 15:22:16 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// Game
# define HEIGHT		512
# define WIDTH		1024
# define SPEED		0.15
# define ROT		48

// Hooks
# define ESC		53
# define W			13
# define A			0
# define S			1
# define D			2
# define RED_CROSS	17
# define UP_ARR		126
# define LEFT_ARR	123
# define DOWN_ARR	125
# define RIGHT_ARR	124

// Messages
# define EXIT_S		"Thanks for playing, bye!\n"

// Errors
# define ER_ARG		"\033[0;31mError\033[0;39m\n--> Wrong number of arguments\n"
# define ER_EMP		"\033[0;31mError\033[0;39m\n--> Empty file\n"
# define ER_EX		"\033[0;31mError\033[0;39m\n--> Wrong file extension\n"
# define ER_IC		"\033[0;31mError\033[0;39m\n--> Invalid character on map\n"
# define ER_IL		"\033[0;31mError\033[0;39m\n\
--> Invalid line in configuration\n"
# define ER_IP		"\033[0;31mError\033[0;39m\n--> Invalid path\n"
# define ER_MA		"\033[0;31mError\033[0;39m\n--> Memory allocation\n"
# define ER_MLX_AD	"\033[0;31mError\033[0;39m\n--> MLX address failed\n"
# define ER_MLX_IM	"\033[0;31mError\033[0;39m\n--> MLX image failed\n"
# define ER_MLX_IN	"\033[0;31mError\033[0;39m\n--> MLX init failed\n"
# define ER_MP		"\033[0;31mError\033[0;39m\n\
--> More than one player on map\n"
# define ER_NM		"\033[0;31mError\033[0;39m\n--> No map found\n"
# define ER_NP		"\033[0;31mError\033[0;39m\n--> No player found\n"
# define ER_OM		"\033[0;31mError\033[0;39m\n--> Open map\n"
# define ER_RF		"\033[0;31mError\033[0;39m\n--> Reading file failed\n"
# define ER_OP		"\033[0;31mError\033[0;39m\n--> Opening file\n"
# define ER_RGB		"\033[0;31mError\033[0;39m\n--> RGB format\n"

#endif /* DEFINE_H */