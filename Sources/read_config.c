/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:04 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/27 16:18:18 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	free_split(char **split)
{
	free(split[2]);
	free(split[1]);
	free(split[0]);
	free(split);
}

int	init_color(t_global *d, char *line, int *color)
{
	int		i;
	char	**split;

	i = 0;
	while (line[i] == ' ')															// Passer les espaces en début de ligne
		i++;
	split = ft_split(d, &line[i + 1], ',');											// À protéger pour être sûr qu'il n'y ait que 3 éléments
	if (ft_atoi(split[0]) < 0 || 0xff < ft_atoi(split[0]) ||
		ft_atoi(split[1]) < 0 || 0xff < ft_atoi(split[1]) ||
		ft_atoi(split[2]) < 0 || 0xff < ft_atoi(split[2]))
		ft_exit(d, "Configuration error (4)\n");
	*color = (ft_atoi(split[0]) * 0x10000) + (ft_atoi(split[1]) * 0x100) + ft_atoi(split[2]);
	free_split(split);
	return (i);
}

void	init_colors(t_global *d, char *line)
{
	int		i;
	int		color;

	i = init_color(d, line, &color);
	if (line[i] == 'F')
	{
		d->map->floor = color;
		d->flags->f++;
	}
	else if (line[i] == 'C')
	{
		d->map->ceiling = color;
		d->flags->c++;
	}
}

void	export_path(t_global *d, char **str, char **path)
{
	*str = ft_strdup(*path);
	if (!*str) // assez protege ?
		ft_exit(d, ER_MA);
	free(*path);
}

void	init_files(t_global *d, char *line)			// Possible de raccourcir la fonction en incrémentant les flags directement dans export_path
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (line[i] == ' ')														// Sauter les espaces avant les 2 lettres
		i++;
	j = i + 2;																	// Sauter les espaces après les 2 lettres
	while (line[j] == ' ')
		j++;
	path = ft_strtrim(&line[j], "\n");
	if (line[i] == 'N' && !d->flags->no)
	{
		export_path(d, &d->map->wall_n->path, &path);
		d->flags->no++;
	}
	else if (line[i] == 'S' && !d->flags->so)
	{
		export_path(d, &d->map->wall_s->path, &path);
		d->flags->so++;
	}
	else if (line[i] == 'E' && !d->flags->ea)
	{
		export_path(d, &d->map->wall_e->path, &path);
		d->flags->ea++;
	}
	else if (line[i] == 'W' && !d->flags->we)
	{
		export_path(d, &d->map->wall_w->path, &path);
		d->flags->we++;
	}
	else
	{
		ft_exit(d, "Configuration error (1)\n");
	}
}

void	init_flags(t_global *d)
{
	d->flags->no = 0;
	d->flags->so = 0;
	d->flags->ea = 0;
	d->flags->we = 0;
	d->flags->c = 0;
	d->flags->f = 0;
	d->flags->lines = 0;
}

int	open_fd(t_global *d, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 1 || fd > OPEN_MAX || read(fd, NULL, 0) < 0 || ft_strlen(file) < 4)					// Protéger fd ET pré-vérifier l'extension
	{
		close(fd);
		ft_exit(d, "Error: invalid path\n");
	}
	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))						// Vérifier l'extension
	{
		close(fd);
		ft_exit(d, ER_EX);
	}
	return (fd);
}

void	read_config(t_global *d, char *file)
{
	int			fd;
	char		*line;
	int			i;

	fd = open_fd(d, file);
	init_flags(d);
	line = get_next_line(fd);													// Lire la première ligne et vérifier qu'elle n'est pas vide
	while (!d->flags->no || !d->flags->so || !d->flags->ea ||
		!d->flags->we || !d->flags->f || !d->flags->c)										// Vérifier le nombre d'éléments qui ont déjà été initialisés
	{
		if (!line)
		{
			free(line);
			close(fd);
			ft_exit(d, ER_EMP);
		}
		d->flags->lines++;
		i = 0;
		while (line[i] == ' ')													// Passer les éventuels espaces en début de ligne
			i++;
		if ((!ft_strncmp(&line[i], "NO", 2)) ||
			(!ft_strncmp(&line[i], "SO", 2)) ||
			(!ft_strncmp(&line[i], "EA", 2)) ||
			(!ft_strncmp(&line[i], "WE", 2)))
			init_files(d, line);								// Initialisation des fichiers de texture
		else if ((!ft_strncmp(&line[i], "F", 1)) ||
			(!ft_strncmp(&line[i], "C", 1)))
			init_colors(d, line);								// Initialisation des couleurs sol/plafond
		else if (line[i] == '\n')
			;
		else
			ft_exit(d, "Configuration error (3)\n");								// Erreur si n'importe quel autre caractère est trouvé
		free(line);
		line = get_next_line(fd);												// Retour en début de boucle si fin de ligne
	}
	close(fd);
	read_map(d, file);														// Lecture de la map (1)
	// free(d->map->wall_n->path);
	// free(d->map->wall_s->path);
	// free(d->map->wall_e->path);
	// free(d->map->wall_w->path);
	free(line);
}
