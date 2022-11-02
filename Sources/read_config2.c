/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:04 by hcremers          #+#    #+#             */
/*   Updated: 2022/11/02 12:12:49 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	init_color2(t_global *d, char *line)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(d, line, ',');
	if (!split)
		ft_exit(d, ER_MA);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free(split[2]);
	free(split[1]);
	free(split[0]);
	free(split);
	if (r < 0x0 || 0xff < r || g < 0x0 || 0xff < g || b < 0x0 || 0xff < b)
		ft_exit(d, ER_RGB);
	return ((r * 0x10000) + (g * 0x100) + b);
}

/* ----------------------------------------------------------------------------
The init_color2 function uses ft_split to separately get the red, green and
blue colors on the received line, in the form of an int between 0 and 255. It
then transforms these 3 integers into a single integer which will be the one
the mlx will use.
An error is sent if one of the 3 colors is out of range.
NB: ft_split has been modified to send an error if it does not find exactly 3
colors.
---------------------------------------------------------------------------- */

void	init_color1(t_global *d, char *line, char flag)
{
	int		color;

	color = init_color2(d, line);
	if (flag == 'F')
	{
		d->map->floor = color;
		d->flags->f++;
	}
	else if (flag == 'C')
	{
		d->map->ceiling = color;
		d->flags->c++;
	}
}

/* ----------------------------------------------------------------------------
The init_color1 function fetches the int returned by init_color2 and assigns it
to the corresponding variable, as well as incrementing the corresponding flag.
---------------------------------------------------------------------------- */

void	export_path(t_global *d, char **str, char *path, int *flag)
{
	*str = ft_strdup(path);
	if (!*str)
	{
		free(path);
		ft_exit(d, ER_MA);
	}
	*flag += 1;
	free(path);
}

void	init_files(t_global *d, char *line, char flag)
{
	int		j;
	char	*path;

	j = 0;
	while (line[j] == ' ')
		j++;
	path = ft_strtrim(&line[j], "\n");
	if (!path)
		ft_exit(d, ER_MA);
	if (flag == 'N' && !d->flags->no)
		export_path(d, &d->map->wall_n->path, path, &d->flags->no);
	else if (flag == 'S' && !d->flags->so)
		export_path(d, &d->map->wall_s->path, path, &d->flags->so);
	else if (flag == 'E' && !d->flags->ea)
		export_path(d, &d->map->wall_e->path, path, &d->flags->ea);
	else if (flag == 'W' && !d->flags->we)
		export_path(d, &d->map->wall_w->path, path, &d->flags->we);
	else
	{
		free(path);
		ft_exit(d, ER_IL);
	}
}

/* ----------------------------------------------------------------------------
The init_files and export_path functions work in harmony to isolate the paths
to the texture files.
init_files receives the configuration line starting from the first character
after the identifier and removes the leading spaces and the line break to keep
only the path.
It then sends this string to export_path which copies it into the right struc-
ture, as well as incrementing the corresponding flag.
---------------------------------------------------------------------------- */
