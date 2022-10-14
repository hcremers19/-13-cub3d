/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:47:15 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/13 15:31:26 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define __null (void *)0

typedef struct s_map
{
	char	**matrix;
	int		height;
	int		width;
}	t_map;

void	ft_error(char *error);
int		ft_strlen(char *str);
char	*get_next_line(int fd);
void	ft_putstr_fd(char *str, int fd);	// Juste pour les tests
void	ft_putnbr_fd(int n, int fd);		// Juste pour les tests
void	ft_putchar_fd(char c, int fd);		// Juste pour les tests

void	get_dimensions(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);													// Ouvrir le fichier pour trouver les dimensions de la zone de map
	if (fd < 1 || read(fd, NULL, 0) < 0)
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
	map->width = ft_strlen(line) - 1;											// (1)
	ft_putstr_fd("map->width = ", 1); ft_putnbr_fd(map->width, 1); ft_putchar_fd(10, 1);
	while (line)
	{
		map->height++;															// Déterminer la hauteur en l'incrémentant à chaque nouvelle ligne
		len = ft_strlen(line) - 1;												// (1)
		if (map->width < len)
			map->width = len;													// Déterminer la largeur en gardant toujours la ligne la plus longue
		free(line);
		line = get_next_line(fd);
	}
	ft_putstr_fd("map->height = ", 1); ft_putnbr_fd(map->height, 1); ft_putchar_fd(10, 1);
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
	int		y;
	int		x;
	char	*line;
	int		len;

	fd = open(file, O_RDONLY);													// Ouvrir le fichier pour remplir la matrice
	y = 0;
	while (y < map->height)
	{
		line = get_next_line(fd);
		len = ft_strlen(line) - 1;												// (1)
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
	}
	close(fd);
}

void	print_matrix(t_map *map)
{
	int	y;
	int	x;

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
			if (y == 0 || x == 0 || y == map->height - 1 || x == map->width - 1)	// Vérifier qu'aucun 0 ne se trouve au bord de la zone de map
			{
				if (map->matrix[y][x] != ' ' && map->matrix[y][x] != '1')
				{
					ft_putstr_fd("x = ", 1); ft_putnbr_fd(x, 1); ft_putstr_fd(", y = ", 1); ft_putnbr_fd(y, 1); ft_putchar_fd(10, 1);
					ft_putchar_fd('\'', 1); ft_putchar_fd(map->matrix[y][x], 1); ft_putchar_fd('\'', 1); ft_putchar_fd('\n', 1); 
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
						ft_putstr_fd("x = ", 1); ft_putnbr_fd(x, 1); ft_putstr_fd(", y = ", 1); ft_putnbr_fd(y, 1); ft_putchar_fd(10, 1);
						ft_putchar_fd('\'', 1); ft_putchar_fd(map->matrix[y][x], 1); ft_putchar_fd('\'', 1); ft_putchar_fd('\n', 1); 
						ft_error("Error2: open map\n");
					}
					if (map->matrix[y][x] != '0')								// Compter le nombre de N, S, W ou E trouvés
						player++;
				}
				else if (map->matrix[y][x] != '1' && map->matrix[y][x] != ' ')
				{
					ft_putstr_fd("x = ", 1); ft_putnbr_fd(x, 1); ft_putstr_fd(", y = ", 1); ft_putnbr_fd(y, 1); ft_putchar_fd(10, 1);
					ft_putchar_fd('\'', 1); ft_putchar_fd(map->matrix[y][x], 1); ft_putchar_fd('\'', 1); ft_putchar_fd('\n', 1); 
					ft_error("Error: Invalid character on map\n");
				}
			}
			x++;
		}
		y++;
	}
	if (!player)
		ft_error("Error: no player on map\n");
	if (player > 1)
		ft_error("Error: more than one player on map\n");
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
	print_matrix(map);
	check_map(map);
}

// (1) Pas la méthode optimale, nécessitera peut-être une modification.
// 	->	Le but de cette manœuvre est de ne pas garder de retour à la ligne dans
// 		la matrice (ni de caractères nuls d'ailleurs), mais uniquement les ca-
// 		ractères qui concernent la map.
//		Dans la méthode actuelle, cela est réalisé en supprimant le dernier ca-
// 		ractère de chaque ligne que get_next_line renvoie.
//		Seulement, cette méthode n'est pas optimale parce que chaque ligne lue
// 		n'est pas forcément terminée par un retour à la ligne, or actuellement
// 		le caractère final est systématiquement supprimé, même si ce dernier
// 		n'est pas un retour à la ligne.
//		La méthode optimale consisterait donc à modifier la fonction
// 		get_next_line afin qu'elle ne garde pas de retour à la ligne quand elle
// 		en trouve un à la fin de la ligne qu'elle va renvoyer.
