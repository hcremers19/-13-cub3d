/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:04 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/28 15:59:06 by hcremers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	init_color2(t_global *d, char *line)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(d, line, ',');
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0x0 || 0xff < r || g < 0x0 || 0xff < g || b < 0x0 || 0xff < b)
		ft_exit(d, ER_RGB);
	free(split[2]);
	free(split[1]);
	free(split[0]);
	free(split);
	return ((r * 0x10000) + (g * 0x100) + b);
}

/* ----------------------------------------------------------------------------
La fonction init_color2 utilise ft_split pour récupérer séparément les couleurs
rouge, vert et bleu se trouvant sur la ligne reçue, sous forme d'un int compris
entre 0 et 255. Elle transforme ensuite ces 3 entiers en un seul qui sera celui
que pourra utiliser la mlx.
Une erreur est renvoyée si l'une des 3 couleurs est en-dehors du range.
NB : ft_split a été modifié pour renvoyer une erreur s'il ne trouve pas exacte-
ment 3 couleurs.
---------------------------------------------------------------------------- */

void	init_color1(t_global *d, char *line, char flag)
{
	int		color;

	color = init_color2(d, line);
	if (flag == 'F')
	{
		d->map->floor = color;
		d->flags->f++;
	}
	else if (flag == 'C')
	{
		d->map->ceiling = color;
		d->flags->c++;
	}
}

/* ----------------------------------------------------------------------------
La fonction init_color1 récupère l'int renvoyé par init_color2 et l'assigne à
la variable correspondante, en en profitant pour incrémenter le flag correspon-
dant
---------------------------------------------------------------------------- */

void	export_path(t_global *d, char **str, char *path, int *flag)
{
	*str = ft_strdup(path);
	if (!*str) // assez protege ?
		ft_exit(d, ER_MA);
	*flag += 1;
	free(path);
}

void	init_files(t_global *d, char *line, char flag)
{
	int		j;
	char	*path;

	j = 0;
	while (line[j] == ' ')
		j++;
	path = ft_strtrim(&line[j], "\n");
	if (flag == 'N' && !d->flags->no)
		export_path(d, &d->map->wall_n->path, path, &d->flags->no);
	else if (flag == 'S' && !d->flags->so)
		export_path(d, &d->map->wall_s->path, path, &d->flags->so);
	else if (flag == 'E' && !d->flags->ea)
		export_path(d, &d->map->wall_e->path, path, &d->flags->ea);
	else if (flag == 'W' && !d->flags->we)
		export_path(d, &d->map->wall_w->path, path, &d->flags->we);
	else
		ft_exit(d, ER_IL);
}

/* ----------------------------------------------------------------------------
Les fonctions init_files et export_path fonctionnent en harmonie pour isoler
les chemins d'accès aux fichiers de texture.
init_files reçoit la ligne de configuration à partir du premier caractère après
l'identificateur et supprime les espaces de début de ligne et le retour à la
ligne pour ne garder que le path.
Elle envoie ensuite cette string à export_path qui la copie dans la bonne
structure, et en profite pour incrémenter le flag correspondant.
---------------------------------------------------------------------------- */

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
