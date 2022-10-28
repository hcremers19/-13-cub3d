/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:22:06 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/28 17:12:30 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// Game
# define WIDTH 1024
# define HEIGHT 512
# define SPEED 0.15
# define ROT (M_PI/48) // = 0.130899693899575

// Hook
# define ESC 53
# define W 13
# define D 2
# define S 1
# define A 0
# define UP_ARR 126
# define DOWN_ARR 125
# define RIGHT_ARR 124
# define LEFT_ARR 123
# define RED_CROSS 17

// Message
# define EXIT_S "Thanks for playing, bye!\n"

// Error
# define ER_ARG "Error\n--> Wrong number of arguments\n"
# define ER_MA "Error\n--> Malloc allocation.\n"
# define ER_EX "Error\n--> Wrong file extension\n"
# define ER_EMP "Error\n--> Empty file\n"
# define ER_NP "Error\n--> No player on map\n"
# define ER_CHA "Error\n--> Invalid character on map\n"
# define ER_MLX_IN "Error\n--> MLX init failed\n"
# define ER_MLX_IM "Error\n--> MLX image failed\n"
# define ER_MLX_AD "Error\n--> MLX address failed\n"
# define ER_OP "Error\n--> Opening file.\n"

#endif /* DEFINE_H */
