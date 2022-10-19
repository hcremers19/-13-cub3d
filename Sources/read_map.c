/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:47:15 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/19 16:25:20 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	free_all(t_map *map)
{
	int	i;

	i = 0;
	while (i <= map->height)
	{
		free(map->matrix[i]);
		i++;
	}
	free(map->matrix);
	free(map);
}
void	check_map(t_map *map)
{
	int	y;
	int	x;
	int	player;

	player = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (y == 0 || x == 0 || y == map->height - 1 || x == map->width - 1)// Vérifier qu'aucun 0 ne se trouve au bord de la zone de map
			{
				if (map->matrix[y][x] != ' ' && map->matrix[y][x] != '1')
				{
					free_all(map);
					ft_error("Error1: open map\n");
				}
			}
			else
			{
				if (map->matrix[y][x] == '0' ||
					map->matrix[y][x] == 'N' ||
					map->matrix[y][x] == 'E' ||
					map->matrix[y][x] == 'W' ||
					map->matrix[y][x] == 'S')									// Vérifier qu'aucun 0 ne soit à côté d'un espace
				{
					if (map->matrix[y - 1][x] == ' ' ||
						map->matrix[y + 1][x] == ' ' ||
						map->matrix[y][x - 1] == ' ' ||
						map->matrix[y][x + 1] == ' ')
					{
						free_all(map);
						ft_error("Error2: open map\n");
					}
					if (map->matrix[y][x] != '0')								// Trouver le joueur
					{
						if (player)
						{
							free_all(map);
							ft_error("Error: more than one player on map\n");
						}
						else
						{
							player++;
							map->orientation = map->matrix[y][x];
							map->player_x = x;
							map->player_y = y;
						}
					}
				}
				else if (map->matrix[y][x] != '1' && map->matrix[y][x] != ' ')
				{
					free_all(map);
					ft_error("Error: Invalid character on map\n");
				}
			}
			x++;
		}
		y++;
	}
	if (!player)
	{
		free_all(map);
		ft_error("Error: no player on map\n");
	}
}

void	print_matrix(t_map *map)												// Juste pour les tests
{
	int	y;
	int	x;

	ft_putstr_fd("map->width = ", 1); ft_putnbr_fd(map->width, 1); ft_putchar_fd(10, 1);
	ft_putstr_fd("map->height = ", 1); ft_putnbr_fd(map->height, 1); ft_putchar_fd(10, 1);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_putchar_fd(map->matrix[y][x], 1);
			x++;
		}
		ft_putchar_fd(10, 1);
		y++;
	}
}

void	fill_matrix(char *file, t_map *map, int lines)
{
	int		fd;
	int		i;
	int		y;
	int		x;
	char	*line;
	char	*trim;
	int		len;

	fd = open(file, O_RDONLY);													// Ouvrir le fichier pour remplir la matrice
	line = get_next_line(fd);
	i = 0;
	while (i < lines)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	trim = ft_strtrim(line, "\n");
	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(trim);													// (1)
		x = 0;
		while (x < len)
		{
			map->matrix[y][x] = line[x];										// Copier les caractères du fichier dans la matrice
			x++;
		}
		while (x < map->width)
		{
			map->matrix[y][x] = ' ';											// Remplir les cases manquantes avec des espaces
			x++;
		}
		y++;
		free(trim);
		free(line);
		line = get_next_line(fd);
		trim = ft_strtrim(line, "\n");
	}
	free(line);
	close(fd);
}

void	alloc_map(t_map *map)
{
	int	i;

	map->matrix = (char **)malloc(sizeof(char *) * map->height);
	if (!map->matrix)
		ft_error("Allocation error\n");
	i = 0;
	while (i <= map->height)
	{
		map->matrix[i] = (char *)malloc(sizeof(char) * map->width);
		if (!map->matrix[i])
		{
			while (i >= 0)
				free(map->matrix[i--]);
			free(map->matrix);
			ft_error("Allocation error\n");
		}
		i++;
	}
}

void	get_dimensions(char *file, t_map *map, int lines)
{
	int		fd;
	char	*line;
	char	*trim;
	int		len;
	int		i;

	fd = open(file, O_RDONLY);													// Ouvrir le fichier pour trouver les dimensions de la zone de map
	if (fd < 1 || read(fd, NULL, 0) < 0)
		ft_error("Error: invalid path\n");										// Doit peut-être être closed
	line = get_next_line(fd);
	i = 0;
	while (i < lines)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (!line)
	{
		free(line);
		free(map);
		close(fd);
		ft_error("Error: empty map\n");
	}
	trim = ft_strtrim(line, "\n");
	map->height = 0;
	map->width = ft_strlen(trim);
	while (line)
	{
		map->height++;															// Déterminer la hauteur en l'incrémentant à chaque nouvelle ligne
		len = ft_strlen(trim);
		if (map->width < len)
			map->width = len;													// Déterminer la largeur en gardant toujours la ligne la plus longue
		free(trim);
		free(line);
		line = get_next_line(fd);
		trim = ft_strtrim(line, "\n");
	}
	free(line);
	close(fd);
}

void	read_map(char *file, int lines)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error("Allocation error\n");
	get_dimensions(file, map, lines);
	alloc_map(map);
	fill_matrix(file, map, lines);
	print_matrix(map);															// Juste pour les tests
	check_map(map);
	free_all(map);
}
