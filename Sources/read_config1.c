/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:04 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/28 16:15:21 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	init_flags(t_global *d)
{
	d->flags->no = 0;
	d->flags->so = 0;
	d->flags->ea = 0;
	d->flags->we = 0;
	d->flags->c = 0;
	d->flags->f = 0;
	d->flags->lines = 0;
	d->flags->players = 0;
}

/* ----------------------------------------------------------------------------
La fonction init_flags initialise les variables de la structure t_flags, qui
serviront pour différentes fonctions de la partie "parsing" du programme.
---------------------------------------------------------------------------- */

int	open_fd(t_global *d, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 1 || fd > OPEN_MAX || read(fd, NULL, 0) < 0 || ft_strlen(file) < 4)
	{
		close(fd);
		ft_exit(d, ER_IP);
	}
	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))
	{
		close(fd);
		ft_exit(d, ER_EX);
	}
	return (fd);
}

/* ----------------------------------------------------------------------------
La fonction open_fd protège l'ouverture du fichier et vérifie que son extension
est correcte, elle renvoie une erreur si quelque chose ne se passe pas comme
prévu.
---------------------------------------------------------------------------- */

void	read_config2(t_global *d, char *line)
{
	int	i;

	d->flags->lines++;
	i = 0;
	while (line[i] == ' ')
			i++;
	if (!ft_strncmp(&line[i], "NO", 2) || !ft_strncmp(&line[i], "SO", 2) \
		|| !ft_strncmp(&line[i], "EA", 2) || !ft_strncmp(&line[i], "WE", 2))
		init_files(d, &line[i + 2], line[i]);
	else if ((!ft_strncmp(&line[i], "F", 1)) || (!ft_strncmp(&line[i], "C", 1)))
		init_color1(d, &line[i + 1], line[i]);
	else if (line[i] == '\n')
		;
	else
		ft_exit(d, ER_IL);
}

void	read_config1(t_global *d, char *file)
{
	int			fd;
	char		*line;

	fd = open_fd(d, file);
	init_flags(d);
	line = get_next_line(fd);
	while (!d->flags->no || !d->flags->so || !d->flags->ea \
		|| !d->flags->we || !d->flags->f || !d->flags->c)
	{
		if (!line)
		{
			free(line);
			close(fd);
			ft_exit(d, ER_EMP);
		}
		read_config2(d, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	read_map(d, file);
}

/* ----------------------------------------------------------------------------
La fonction read_config a dû être divisée à cause de la Norme.
Elle lit les premières lignes du fichier de configuration et parse les données
en fonction de ce qu'elle trouve. Elle ignore d'abord les éventuels espaces en
début de ligne puis vérifie que ce qui suit est l'un des identificateurs qu'el-
le connaît ou un renvoi à la ligne. Si ce n'est pas le cas, elle renvoie une
erreur.
À chaque nouvelle ligne, elle s'assure qu'il reste encore des éléments à trou-
ver, car si les 6 éléments nécessaires à la configuration ont déjà été trouvés,
la fonction s'arrête et le programme passe à la lecture de la map.
Elle compte aussi le nombre de lignes que comporte cette partie du fichier afin
que la fonction read_map puisse les ignorer et lire directement la map texte.
---------------------------------------------------------------------------- */
