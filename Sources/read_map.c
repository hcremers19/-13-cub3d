/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:47:15 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/28 15:20:25 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	valid_map(t_global *d)
{
	int	y;
	int	x;

	y = 0;
	while (y < d->map->map_height)
	{
		x = 0;
		while (x < d->map->map_width)
		{
			if ((y == 0 || x == 0 || y == d->map->map_height - 1 || \
				x == d->map->map_width - 1) && (d->map->matrix[y][x] == '0'))
				ft_exit(d, ER_OM);
			else if ((d->map->matrix[y][x] == '0') && \
				(d->map->matrix[y - 1][x] == ' ' || \
				d->map->matrix[y + 1][x] == ' ' || \
				d->map->matrix[y][x - 1] == ' ' || \
				d->map->matrix[y][x + 1] == ' '))
				ft_exit(d, ER_OM);
			x++;
		}
		y++;
	}
}

/* ----------------------------------------------------------------------------
La fonction valid_map parcourt la matrice pour s'assurer que la map est bien
fermée, c'est-à-dire que la zone jouable (0) est entièrement entourée par des
murs (1).
Elle vérifie donc qu'aucun 0 ne se trouve au bord de la zone brute de map, puis
qu'aucun espace (zone non-jouable) ne se trouve à côté d'un 0.
---------------------------------------------------------------------------- */

// void	print_matrix(t_global *d)
// {
// 	int	y;
// 	int	x;

// 	ft_putstr_fd("d->map->map_width = ", 1);
// 	ft_putnbr_fd(d->map->map_width, 1);
// 	ft_putchar_fd(10, 1);
// 	ft_putstr_fd("d->map->map_height = ", 1);
// 	ft_putnbr_fd(d->map->map_height, 1);
// 	ft_putchar_fd(10, 1);
// 	y = 0;
// 	while (y < d->map->map_height)
// 	{
// 		x = 0;
// 		while (x < d->map->map_width)
// 		{
// 			ft_putchar_fd(d->map->matrix[y][x], 1);
// 			x++;
// 		}
// 		ft_putchar_fd(10, 1);
// 		y++;
// 	}
// }

void	valid_char(t_global *d, char *line, int x, int y)
{
	if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E' || line[x] == 'W')
	{
		if (d->flags->players)
			ft_exit(d, ER_MP);
		else
		{
			d->flags->players++;
			d->player->orientation = line[x];
			d->player->pos_x = x + 0.20;
			d->player->pos_y = y + 0.20;
			d->map->matrix[y][x] = '0';
		}
	}
	else if (line[x] == '0' || line[x] == '1' || line[x] == ' ')
		d->map->matrix[y][x] = line[x];
	else
		ft_exit(d, ER_IC);
}

/* ----------------------------------------------------------------------------
Si le caractère analysé par la fonction valid_char correspond à la position de
départ du joueur, elle conserve l'orientation et la position de ce dernier,
puis remplace le caractère en question par un '0'.
Dans le cas contraire, elle le copie simplement dans la matrice, à condition
qu'il soit valide.
---------------------------------------------------------------------------- */

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
			valid_char(d, line, x, y);
		while (x < d->map->map_width)
			d->map->matrix[y][x++] = ' ';
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
		ft_exit(d, ER_OP);
	line = get_next_line(fd);
	i = 0;
	while (i < d->flags->lines)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	fill_matrix2(d, line, fd);
	if (!d->flags->players)
		ft_exit(d, ER_NP);
	close(fd);
}

/* ----------------------------------------------------------------------------
La fonction fill_matrix a dû être coupée en 2 à cause de la Norme.
Elle parcourt une deuxième fois la map texte afin d'en extraire les caractères
et les insérer dans le tableau à 2 dimensions "matrix".
Comme dans get_dimensions, les premières lignes du fichier sont ignorées grâce
au flag "lines". Les lignes suivantes sont ensuite lues avec get_next_line et
les caractères sont copiés un à un dans la matrice, en ignorant le retour à la
ligne s'il y en a un.
Pour les lignes plus petites que la largeur de la zone brute de map, les espa-
ces mémoire manquants sont remplis avec des ' ', caractère correspondant aux
cases situées en-dehors de la zone jouable.
---------------------------------------------------------------------------- */

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

/* ----------------------------------------------------------------------------
La fonction alloc_map initialise le tableau à 2 dimensions "matrix" en lui al-
louant juste assez de mémoire pour plus tard y insérer la map.
---------------------------------------------------------------------------- */

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
		d->map->map_height++;
		len = ft_strlen(trim);
		if (d->map->map_width < len)
			d->map->map_width = len;
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

	fd = open(file, O_RDONLY);
	if (fd < 1 || fd > OPEN_MAX || read(fd, NULL, 0) < 0)
		ft_exit(d, ER_OP);
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
		close(fd);
		ft_exit(d, ER_NM);
	}
	get_dimensions2(d, line, fd);
	close(fd);
}

/* ----------------------------------------------------------------------------
La fonction get_dimensions a dû être coupée en 2 à cause de la Norme.
Elle consiste à parcourir une première fois la map texte afin de déterminer la
hauteur et la largeur du rectangle brut dans lequel est inscrite la map. On dé-
termine la hauteur avec le nombre de lignes qui ont été lues la largeur avec la
taille de la ligne la plus longue ayant été lue.
Ces valeurs permettront plus tard d'allouer juste assez de mémoire pour la mat-
rice.
Les lignes de texte sont lues avec get_next_line.
Le flag "lines" correspond au nombre de lignes à passer dans le fichier de con-
figuration pour atteindre directement les lignes qui concernent la map et igno-
rer celle des textures.
L'utilisation d'une variable temporaire "trim" était nécessaire pour pouvoir
free le retour de ft_strtrim.
---------------------------------------------------------------------------- */

void	read_map(t_global *d, char *file)
{
	get_dimensions1(d, file);
	alloc_map(d);
	fill_matrix1(d, file);
	// print_matrix(d);
	valid_map(d);
}
