/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:04 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/19 16:34:26 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

void	free_split(char **split)
{
	free(split[2]);
	free(split[1]);
	free(split[0]);
	free(split);
}

int	init_color(char *line, int *color)
{
	int	i;
	char **split;

	i = 0;
	while (line[i] == ' ')															// Passer les espaces en début de ligne
		i++;
	split = ft_split(&line[i + 1], ',');											// À protéger pour être sûr qu'il n'y ait que 3 éléments
	if (ft_atoi(split[0]) < 0 || 0xff < ft_atoi(split[0]) ||
		ft_atoi(split[1]) < 0 || 0xff < ft_atoi(split[1]) ||
		ft_atoi(split[2]) < 0 || 0xff < ft_atoi(split[2]))
		ft_error("Configuration error (4)\n");
	*color = (ft_atoi(split[0]) * 0x10000) + (ft_atoi(split[1]) * 0x100) + ft_atoi(split[2]);
	free_split(split);
	return (i);
}

void	init_colors(char *line, t_elements *emts)
{
	int		i;
	int		color;

	i = init_color(line, &color);
	if (line[i] == 'F')
	{
		emts->F = color;
		emts->F_flag++;
	}
	else if (line[i] == 'C')
	{
		emts->C = color;
		emts->C_flag++;
	}
}

void	export_path(char **str, char **path)
{
	*str = ft_strdup(*path);
	free(*path);
}

void	init_files(char *line, t_elements *emts)			// Possible de raccourcir la fonction en incrémentant les flags directement dans export_path
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] == ' ')
		i++;
	path = ft_strtrim(&line[i + 2], "\n");
	if (line[i] == 'N' && !emts->NO_flag)
	{
		export_path(&emts->NO, &path);
		emts->NO_flag++;
	}
	else if (line[i] == 'S' && !emts->SO_flag)
	{
		export_path(&emts->SO, &path);
		emts->SO_flag++;
	}
	else if (line[i] == 'E' && !emts->EA_flag)
	{
		export_path(&emts->EA, &path);
		emts->EA_flag++;
	}
	else if (line[i] == 'W' && !emts->WE_flag)
	{
		export_path(&emts->WE, &path);
		emts->WE_flag++;
	}
	else
	{
		ft_error("Configuration error (1)\n");
	}
}

void	init_flags(t_elements *emts)
{
	emts->NO_flag = 0;
	emts->SO_flag = 0;
	emts->EA_flag = 0;
	emts->WE_flag = 0;
	emts->C_flag = 0;
	emts->F_flag = 0;
	emts->lines = 0;
}

int	open_fd(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 1 || read(fd, NULL, 0) < 0 || ft_strlen(file) < 4)					// Protéger fd ET pré-vérifier l'extension
	{
		close(fd);
		ft_error("Error: invalid path\n");
	}
	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))						// Vérifier l'extension
	{
		close(fd);
		ft_error("Error: wrong file extension\n");
	}
	return (fd);
}

void	read_config(char *file)
{
	int			fd;
	char		*line;
	t_elements	emts;	// Éléments parsés
	int			i;

	fd = open_fd(file);
	init_flags(&emts);
	line = get_next_line(fd);													// Lire la première ligne et vérifier qu'elle n'est pas vide
	while (!emts.NO_flag || !emts.SO_flag || !emts.EA_flag ||
		!emts.WE_flag || !emts.F_flag || !emts.C_flag)										// Vérifier le nombre d'éléments qui ont déjà été initialisés
	{
		if (!line)
		{
			free(line);
			close(fd);
			ft_error("Error: empty file\n");
		}
		emts.lines++;
		i = 0;
		while (line[i] == ' ')													// Passer les éventuels espaces en début de ligne
			i++;
		if ((!ft_strncmp(&line[i], "NO", 2)) ||
			(!ft_strncmp(&line[i], "SO", 2)) ||
			(!ft_strncmp(&line[i], "EA", 2)) ||
			(!ft_strncmp(&line[i], "WE", 2)))
			init_files(line, &emts);								// Initialisation des fichiers de texture
		else if ((!ft_strncmp(&line[i], "F", 1)) ||
			(!ft_strncmp(&line[i], "C", 1)))
			init_colors(line, &emts);								// Initialisation des couleurs sol/plafond
		else if (line[i] == '\n')
			;
		else
			ft_error("Configuration error (3)\n");								// Erreur si n'importe quel autre caractère est trouvé
		free(line);
		line = get_next_line(fd);												// Retour en début de boucle si fin de ligne
	}
	close(fd);
	printf("NO: %s\n", emts.NO);
	printf("SO: %s\n", emts.SO);
	printf("EA: %s\n", emts.EA);
	printf("WE: %s\n", emts.WE);
	printf("C: %x\n", emts.C);
	printf("F: %x\n", emts.F);
	read_map(file, emts.lines);														// Lecture de la map (1)
	free(emts.NO);
	free(emts.SO);
	free(emts.EA);
	free(emts.WE);
	free(line);
}
