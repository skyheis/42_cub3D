/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:24:49 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/03 13:09:24 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_infile(char *infile)
{
	int	len;
	int	fd;

	len = ft_strlen(infile);
	fd = open(infile, O_RDONLY);
	if (fd == -1 || len < 5)
		exit(1); //ft_exit();
	close(fd);
	if (!ft_strncmp(&infile[len - 4], ".cub", 5) || infile[len - 5] != '/')
		exit(1);
}

void	ft_read_map(t_map *map, char *file)
{
	int		fd;
	int		b_readed;
	char	*file_memory;

	b_readed = READ_SIZE;
	fd = open(file, O_RDONLY);
	while (b_readed == READ_SIZE)
	{
		file_memory = ft_calloc(READ_SIZE + 1, sizeof(char));
		b_readed = read(fd, file_memory, READ_SIZE);
		if (b_readed == -1)
			exit(1); //ft_exit_map();
		map->map_memory = ft_strjoin_free(map->map_memory, file_memory);
	}
	close(fd);
}

int	ft_substrlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
		i++;
	return (i);
}

void	ft_get_fc_color(char *mapmem, int *i, int *color)
{
	int	times;
	int	atoi;
	int	mult;

	times = 0;
	mult = 1000000;
	*i = *i + 1;
	while (mapmem[*i] == 32)
		*i = *i + 1;
	while (times++ < 3)
	{
		atoi = ft_atoi(&mapmem[*i]);
		if (atoi < 0 || atoi > 255)
			exit(1); //ft_exit_map
		*color += atoi * mult;
		mult /= 1000;
		while (ft_isdigit(mapmem[*i]))
			*i = *i + 1;
		if (mapmem[*i] == ',' ||
			(!mult && (mapmem[*i] == ' ' || mapmem[*i] == '\n')))
			*i = *i + 1;
		else
			exit(1); //ft_exit_map
	}
}


void	ft_wallimage_path(char *mapmem, int *i, char **wallpath)
{
	int	j;

	j = 0;
	*i = *i + 2;
	while (mapmem[*i] == 32)
		*i = *i + 1;
	*wallpath = ft_calloc(ft_substrlen(&mapmem[*i]) + 1, sizeof(char));
	if (!*wallpath)
		exit(1); //ft_exit_map
	while (mapmem[*i] != '\0' && mapmem[*i] != ' ' && mapmem[*i] != '\n')
	{
		*wallpath[j] = mapmem[*i];
		*i = *i + 1;
		j++;
	}
	while (mapmem[*i] == ' ')
		*i = *i + 1;
}

void	ft_set_config(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_memory[i])
	{
		if (!ft_strncmp(&map->map_memory[i], "NO ", 3))
			ft_wallimage_path(map->map_memory, &i, &map->no_file);
		else if (!ft_strncmp(&map->map_memory[i], "SO ", 3))
			ft_wallimage_path(map->map_memory, &i, &map->so_file);
		else if (!ft_strncmp(&map->map_memory[i], "WE ", 3))
			ft_wallimage_path(map->map_memory, &i, &map->we_file);
		else if (!ft_strncmp(&map->map_memory[i], "EA ", 3))
			ft_wallimage_path(map->map_memory, &i, &map->ea_file);
		else if (!ft_strncmp(&map->map_memory[i], "F ", 2))
			ft_get_fc_color(map->map_memory, &i, &map->floor_color);
		else if (!ft_strncmp(&map->map_memory[i], "C ", 2))
			ft_get_fc_color(map->map_memory, &i, &map->cieling_color);
		else
			break ;
		while (map->map_memory[i] == '\n')
			i++;
	}
}

void	ft_init_map(t_map *map)
{
	map->map_memory = NULL;
	map->no_file = NULL;
	map->so_file = NULL;
	map->we_file = NULL;
	map->ea_file = NULL;
	map->floor_color = 0;
	map->cieling_color = 0;
}

/* pass &map and av[1] */
void	ft_get_map(t_map *map, char *filename)
{
	ft_check_infile(filename);
	ft_init_map(map);
	ft_read_map(map);
	ft_set_config(map);
}
