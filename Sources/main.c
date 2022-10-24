/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:13 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/24 20:29:58 by acaillea         ###   ########.fr       */
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

	d->map->wallS->path = "cat.xpm";
	d->map->wallN->path = "cat.xpm";
	d->map->wallE->path = "east.xpm";
	d->map->wallW->path = "east.xpm";
	
	d->map->sky = 0x0000FF;
	d->map->floor = 0x00000000;
	//---------------------------------------------------
	init(d);
	return (0);
}

// To do Alan : 
//	- 1 fct initialisation NULL ptr Wall et Ray
//	- arranger mvt E et W
//	- arranger effet fish eyes
//	- verifier leaks