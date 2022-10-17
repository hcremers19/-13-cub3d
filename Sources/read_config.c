/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:04 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/17 19:55:57 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define __null (void *)0

typedef struct s_elements
{
	int	NO;
	int	SO;
	int	EA;
	int	WE;
	int	F;
	int	C;
}	t_elements;

// Fonctions externes
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, int n);
size_t	ft_strlen(const char *s);
void	ft_error(char *error);
char	*get_next_line(int fd);
void	read_map(char *file);

// Fonctions à coder ici
void	init_flags(t_elements *flags);
int		check_elements(t_elements *flags);
void	init_files(char *line);
void	init_colors(char *line);

void	read_config(char *file)
{
	int			fd;
	char		*line;
	t_elements	flags;
	int			i;

	flags.NO = 0;																// Ranger tout ça dans une fonction d'init
	flags.SO = 0;
	flags.EA = 0;
	flags.WE = 0;
	flags.C = 0;
	flags.F = 0;
	fd = open(file, O_RDONLY);
	if (fd < 1 || read(fd, NULL, 0) < 0 || ft_strlen(file) < 4)					// Protéger fd ET pré-vérifier l'extension
	{
		close(fd);
		ft_error("Error: invalid path\n");
	}
	if (ft_strncmp(file[ft_strlen(file) - 4], ".cub", 4))						// Vérifier l'extension
	{
		close(fd);
		ft_error("Error: wrong file extension\n");
	}
	line = get_next_line(fd);													// Lire la première ligne et vérifier qu'elle n'est pas vide
	if (!line)
	{
		free(line);
		close(fd);
		ft_error("Error: empty file\n");
	}
	while (check_elements(&flags))												// Vérifier le nombre d'éléments qui ont déjà été initiés
	{
		i = 0;
		while (line[i] == ' ')													// Passer les éventuels espaces en début de ligne
			i++;
		if ((!ft_strncmp(line[i], "NO ", 3)) ||
			(!ft_strncmp(line[i], "SO ", 3)) ||
			(!ft_strncmp(line[i], "EA ", 3)) ||
			(!ft_strncmp(line[i], "WE ", 3)))
			init_files(line);													// Initiation des fichiers de texture
		else if ((!ft_strncmp(line[i], "F ", 2)) ||
			(!ft_strncmp(line[i], "C ", 2)))
			init_colors(line);													// Initiation des couleurs sol/plafond
		else if (i == '\n')
		{
			free(line);
			line = get_next_line(fd);											// Retour en début de boucle si fin de ligne
		}
		else
			ft_error("Configuration error\n");									// Erreur si n'importe quel autre caractère est trouvé
	}
	close(fd);
	read_map(file);																// Lecture de la map (1)
}

// (1) Ne pas oublier de préciser le nombre de lignes qui font partie de la
//	configuration et qu'il faudra donc passer pour commencer à lire la map
//	==> Rajouter le comptage des lignes
