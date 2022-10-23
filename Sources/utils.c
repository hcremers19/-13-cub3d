/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: I-lan <I-lan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 23:58:09 by I-lan             #+#    #+#             */
/*   Updated: 2022/10/20 23:59:00 by I-lan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str && str[i])
		i++;
	return(i);
}
