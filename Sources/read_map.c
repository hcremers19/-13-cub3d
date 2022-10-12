/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:47:15 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/12 17:47:28 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

typedef struct s_map
{
	char	**matrix;
	int		height;
	int		width;
}	t_map;

void	ft_error(char *error);
int		ft_strlen(char *str);
char	*get_next_line(int fd);

void	get_dimensions(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);													// Ouvrir le fichier pour trouver les dimensions de la zone de map
	if (fd < 1 || read(fd, (void *)0, 0) < 0)
		ft_error("Error: invalid path\n");
	map->height = 0;
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		map->width = 0;
		close(fd);
		ft_error("Error: empty map\n");
	}
	map->width = ft_strlen(line);
	while (line)
	{
		map->height++;															// Déterminer la hauteur en l'incrémentant à chaque nouvelle ligne
		len = ft_strlen(line);
		if (map->width < len)
			map->width = len;													// Déterminer la largeur en gardant toujours la ligne la plus longue
		free(line);
		line = get_next_line(fd);
	}
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

void	fill_matrix(char *file, t_map *map)
{
	int		fd;
	int		i;
	int		j;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);													// Ouvrir le fichier pour remplir la matrice
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		len = ft_strlen(line);
		j = 0;
		while (j < len)
		{
			map->matrix[i][j] = line[j];										// Copier les caractères du fichier dans la matrice
			j++;
		}
		while (j < map->width)
		{
			map->matrix[i][j] = ' ';											// Remplir les cases manquantes avec des espaces
			j++;
		}
		i++;
	}
	close(fd);
}

void	check_map(t_map *map)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (i == 0 || j == 0 || map->height == 0 || map->width == 0)		// Vérifier qu'aucun 0 ne se trouve au bord de la zone de map
			{
				if (map->matrix[i][j] != ' ' && map->matrix[i][j] != '1')
					ft_error("Error: open map\n");
			}
			else
			{
				if (map->matrix[i][j] == '0' ||
					map->matrix[i][j] == 'N' ||
					map->matrix[i][j] == 'E' ||
					map->matrix[i][j] == 'W' ||
					map->matrix[i][j] == 'S')									// Vérifier qu'aucun 0 ne soit à côté d'un espace
				{
					if (map->matrix[i - 1][j] == ' ' ||
						map->matrix[i + 1][j] == ' ' ||
						map->matrix[i][j - 1] == ' ' ||
						map->matrix[i][j + 1] == ' ')
					{
						ft_error("Error: open map\n");
					}
					if (map->matrix[i][j] != '0')								// Compter le nombre de N, S, W ou E trouvés
						player++;
				}
			}
			j++;
		}
		i++;
	}
	if (!player)
		ft_error("Error: no player on map\n");
	if (player > 1)
		ft_error("Error: more thant one player on map\n");
}

void	read_map(char *file)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error("Allocation error\n");
	get_dimensions(file, map);
	alloc_map(map);
	fill_matrix(file, map); // Tester en revoyant le contenu de la matrice dans un fichier
	check_map(map);
}
