/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:29:13 by acaillea          #+#    #+#             */
/*   Updated: 2022/10/26 04:24:50 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	main(int ac, char **av)
{
	t_global	*d;

	d = (t_global *)malloc(sizeof(t_global));
	if (!d)
	{
		ft_putstr_fd(ER_MA, 1);
		return (0);
	}
	initStruct(d);
	if (ac != 2)
		ft_exit(d, ER_ARG);
	structMalloc(d);
	read_config(d, av[1]);
	init(d);
	return (0);
}

// To do
//	- verifier leaks
