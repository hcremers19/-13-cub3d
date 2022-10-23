/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:13 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/24 00:15:17 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	main(int ac, char **av)
{
	t_global	*d;

	d = (t_global *)malloc(sizeof(t_global));
	if (!d)
		ft_exit(d, ER_MA);
	structMalloc(d);
	//---------------------------------------------------
	// Parsing init
	//---------------------------------------------------
	(void)ac;
	(void)av;
	// map = test_map;

	d->map->sizeX = 10;
	d->map->sizeX = 10;

	d->player->posX = 4; 
	d->player->posY = 4;
	d->player->letter = 'E';

	// d->map->colorN = 0x00FF0000;
	// d->map->colorS = 0x00FF0000;
	// d->map->colorW = 0x00FF0000;
	// d->map->colorE = 0x00FF0000;
	// d->map->colorSky = 0x0000FF;
	// d->map->colorFloor = 0x00000000;
	//---------------------------------------------------
	init(d);
	return (0);
}
