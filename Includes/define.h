/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:22:06 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/28 18:12:15 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// Game
# define HEIGHT		512
# define WIDTH		1024
# define SPEED		0.15
# define ROT		48

// Hook
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

// Message
# define EXIT_S		"Thanks for playing, bye!\n"

// Error
# define ER_ARG		"Error\n--> Wrong number of arguments\n"
# define ER_EMP		"Error\n--> Empty file\n"
# define ER_EX		"Error\n--> Wrong file extension\n"
# define ER_IC		"Error\n--> Invalid character on map\n"
# define ER_IL		"Error\n--> Invalid line in configuration\n"
# define ER_IP		"Error\n--> Invalid path\n"
# define ER_MA		"Error\n--> Memory allocation\n"
# define ER_MLX_AD	"Error\n--> MLX address failed\n"
# define ER_MLX_IM	"Error\n--> MLX image failed\n"
# define ER_MLX_IN	"Error\n--> MLX init failed\n"
# define ER_MP		"Error\n--> More than one player on map\n"
# define ER_NM		"Error\n--> No map found\n"
# define ER_NP		"Error\n--> No player found\n"
# define ER_OM		"Error\n--> Open map\n"
# define ER_OP		"Error\n--> Opening file\n"
# define ER_RGB		"Error\n--> RGB format\n"

#endif /* DEFINE_H */