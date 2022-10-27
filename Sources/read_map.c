/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:47:15 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/27 15:51:11 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

// void	free_all(t_global *d)
// {
// 	int	i;

// 	i = 0;
// 	while (i <= d->map->map_height)
// 	{
// 		free(d->map->matrix[i]);
// 		i++;
// 	}
// 	free(d->map->matrix);
// 	free(d->map);
// }

void	check_map(t_global *d)
{
	int	y;
	int	x;
	int	player;

	player = 0;
	y = 0;
	while (y < d->map->map_height)
	{
		x = 0;
		while (x < d->map->map_width)
		{
			if (y == 0 || x == 0 || y == d->map->map_height - 1 || x == d->map->map_width - 1)// Vérifier que rien d'autre que des 1 ou ' ' ne se trouve au bord de la zone de map
			{
				if (d->map->matrix[y][x] != ' ' && d->map->matrix[y][x] != '1')
				{
					// free_all(d);
					ft_exit(d, "Error1: open map\n");
				}
			}
			else
			{
				if (d->map->matrix[y][x] == '0' ||
					d->map->matrix[y][x] == 'N' ||
					d->map->matrix[y][x] == 'E' ||
					d->map->matrix[y][x] == 'W' ||
					d->map->matrix[y][x] == 'S')									// Vérifier qu'aucun 0/N/E/W/S ne soit à côté d'un espace
				{
					if (d->map->matrix[y - 1][x] == ' ' ||
						d->map->matrix[y + 1][x] == ' ' ||
						d->map->matrix[y][x - 1] == ' ' ||
						d->map->matrix[y][x + 1] == ' ')
					{
						// free_all(d);
						ft_exit(d, "Error2: open map\n");
					}
					if (d->map->matrix[y][x] != '0')								// Trouver le joueur
					{
						if (player)
						{
							// free_all(d);
							ft_exit(d, "Error: more than one player on map\n");
						}
						else
						{
							player++;
							//-----------------------------------------------
							d->player->orientation = d->map->matrix[y][x];
							d->player->pos_x = x + 0.40;
							d->player->pos_y = y + 0.40;
							d->map->matrix[y][x] = 0;
							//-----------------------------------------------
						}
					}
				}
				else if (d->map->matrix[y][x] != '1' && d->map->matrix[y][x] != ' ')
				{
					// free_all(d);
					ft_exit(d, ER_CHA);
				}
			}
			x++;
		}
		y++;
	}
	if (!player)
	{
		// free_all(d);
		ft_exit(d, ER_NP);
	}
}

void	print_matrix(t_global *d)												// Juste pour les tests
{
	int	y;
	int	x;

	ft_putstr_fd("d->map->map_width = ", 1); ft_putnbr_fd(d->map->map_width, 1); ft_putchar_fd(10, 1);
	ft_putstr_fd("d->map->map_height = ", 1); ft_putnbr_fd(d->map->map_height, 1); ft_putchar_fd(10, 1);
	y = 0;
	while (y < d->map->map_height)
	{
		x = 0;
		while (x < d->map->map_width)
		{
			ft_putchar_fd(d->map->matrix[y][x], 1);
			x++;
		}
		ft_putchar_fd(10, 1);
		y++;
	}
}

void	fill_matrix2(t_global *d, char *line, int fd)
{
	int		x;
	int		y;
	int		len;
	char	*trim;

	trim = ft_strtrim(line, "\n");
	free(line);
	y = 0;
	while (y < d->map->map_height)
	{
		len = ft_strlen(trim);
		x = -1;
		while (++x < len)
			d->map->matrix[y][x] = line[x];										// Copier les caractères du fichier dans la matrice
		while (x < d->map->map_width)
			d->map->matrix[y][x++] = ' ';											// Remplir les cases manquantes avec des espaces
		free(trim);
		line = get_next_line(fd);
		trim = ft_strtrim(line, "\n");
		free(line);
		y++;
	}
	free(trim);
}

void	fill_matrix1(t_global *d, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 1 || fd > OPEN_MAX || read(fd, NULL, 0) < 0)
		ft_exit(d, ER_OP);												// Ouvrir le fichier pour remplir la matrice
	line = get_next_line(fd);
	i = 0;
	while (i < d->flags->lines)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	fill_matrix2(d, line, fd);
	close(fd);
}

void	alloc_map(t_global *d)
{
	int	i;

	d->map->matrix = (char **)malloc(sizeof(char *) * d->map->map_height);
	if (!d->map->matrix)
		ft_exit(d, ER_MA);
	i = 0;
	while (i <= d->map->map_height)
	{
		d->map->matrix[i] = (char *)malloc(sizeof(char) * d->map->map_width);
		if (!d->map->matrix[i])
		{
			while (i >= 0)
				free(d->map->matrix[i--]);
			free(d->map->matrix);
			ft_exit(d, ER_MA);
		}
		i++;
	}
}

void	get_dimensions2(t_global *d, char *line, int fd)
{
	char	*trim;
	int		len;

	trim = ft_strtrim(line, "\n");
	free(line);
	d->map->map_height = 0;
	d->map->map_width = ft_strlen(trim);
	while (trim)
	{
		d->map->map_height++;															// Déterminer la hauteur en l'incrémentant à chaque nouvelle ligne
		len = ft_strlen(trim);
		if (d->map->map_width < len)
			d->map->map_width = len;													// Déterminer la largeur en gardant toujours la ligne la plus longue
		free(trim);
		line = get_next_line(fd);
		trim = ft_strtrim(line, "\n");
		free(line);
	}
	free(trim);
}

void	get_dimensions1(t_global *d, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);													// Ouvrir le fichier pour trouver les dimensions de la zone de map
	if (fd < 1 || fd > OPEN_MAX || read(fd, NULL, 0) < 0)
		ft_exit(d, ER_OP);										// Doit peut-être être closed
	line = get_next_line(fd);
	i = 0;
	while (i < d->flags->lines)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (!line)
	{
		free(line);
		// free(map);
		close(fd);
		ft_exit(d, ER_EMP);
	}
	get_dimensions2(d, line, fd);
	close(fd);
}

void	read_map(t_global *d, char *file)
{
	// t_map	*map;

	// map = (t_map *)malloc(sizeof(t_map));
	// if (!map)
	// 	ft_exit(d, "Allocation error\n");
	get_dimensions1(d, file);
	alloc_map(d);
	fill_matrix1(d, file);
	// print_matrix(d);															// Juste pour les tests
	check_map(d);
	// free_all(d);
}
