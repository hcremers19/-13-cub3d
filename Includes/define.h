/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:22:06 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/26 04:33:58 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// Game
# define WIGHT 1024
# define HEIGHT 512
# define SPEED 0.25
# define ROT M_PI/12
# define __null (void *)0

// Hook
# define ESC 53
# define W 13
# define D 2
# define S 1
# define A 0
# define RIGHT_ARR 124
# define LEFT_ARR 123
# define RED_CROSS 17

// Message
# define EXIT_S "Thanks for playing, bye !\n"

// Error
# define ER_ARG "Error: Wrong number of arguments\n"
# define ER_MA "Error: Malloc allocation.\n"
# define ER_EX "Error: Wrong file extension\n"
# define ER_EMP "Error: Empty file\n"
# define ER_NP "Error: No player on map\n"
# define ER_CHA "Error: Invalid character on map\n"
# define ER_MLX_IN "Error: MLX init failed\n"
# define ER_MLX_IM "Error: MLX image failed\n"
# define ER_MLX_AD "Error: MLX address failed\n"
# define ER_OP "Error: Opening file.\n"

#endif /* DEFINE_H */
