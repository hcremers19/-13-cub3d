/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:13:18 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/28 16:13:36 by hcremers         ###   ########.fr       */
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
