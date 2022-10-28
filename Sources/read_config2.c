/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:04 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/28 16:15:58 by hcremers         ###   ########.fr       */
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
