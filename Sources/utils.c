/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaillea <acaillea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:58:09 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/26 03:08:01 by acaillea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	ft_free_mat(char **mat)
{
	int i;

	if (!mat)
		return ;
	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
	return ;
}
