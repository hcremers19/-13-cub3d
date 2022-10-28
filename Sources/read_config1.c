/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:04 by hcremers          #+#    #+#             */
/*   Updated: 2022/10/28 19:06:18 by hcremers         ###   ########.fr       */
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
The init_flags function initializes the variables of the t_flags structure,
which will be used for different functions in the parsing part of the program.
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
The open_fd function protects the opening of the file and checks that its ex-
tension is correct, it sends an error if something goes wrong.
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
The read_config function had to be split in 2 because of the Norm.
It reads the first lines of the configuration file and parses the data accord-
ing to what it finds. It first ignores any leading spaces and then checks that
what follows is either one of the identifiers it recognizes or a line break.
If it is not, it returns an error.
With each new line, it makes sure that there are still elements to be found,
because if all 6 elements needed for the configuration have already been found,
the function stops and the program moves on to reading the map.
It also counts the number of lines in the top part of the file so that the
read_map function can ignore them and read the text map directly.
---------------------------------------------------------------------------- */
