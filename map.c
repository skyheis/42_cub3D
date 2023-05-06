/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:24:49 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/06 16:43:54 by ggiannit         ###   ########.fr       */
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
	if (ft_strncmp(&infile[len - 4], ".cub", 5) || infile[len - 5] == '/')
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

int	ft_set_config(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_memory[i])
	{
		while (map->map_memory[i] == '\n')
			i++;
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
	}
	if (!ft_isallset(map))
		exit(1); //ft_exit_map
	return (i);
}

void	ft_init_map(t_map *map)
{
	map->map_memory = NULL;
	map->map = NULL;
	map->width = 0;
	map->hight = 0;
	map->no_file = NULL;
	map->so_file = NULL;
	map->we_file = NULL;
	map->ea_file = NULL;
	map->floor_color = -1;
	map->cieling_color = -1;
}

/* pass &map and av[1] */
void	ft_printmatrix(char **mat);

void	ft_get_map(t_map *map, char *filename)
{
	int		i;

	ft_check_infile(filename);
	printf("ok check\n");
	ft_init_map(map);
	printf("ok init\n");
	ft_read_map(map, filename);
	printf("ok read\n");
	i = ft_set_config(map);
	printf("ok set\n");
	map->map = ft_splitmap(map, &map->map_memory[i]);
	printf("ok splitmap\n");
	ft_free_null(&map->map_memory);
	ft_findplayer(map);
	printf("ok player\n");
	ft_checkmap(map);
	printf("ok map\n");
	//ft_printmatrix(map->map);
	printf("player:\nx %i\ny %i\nv %c\n", map->player[0], map->player[1], (char) map->player[2]);
}

void	ft_printmatrix(char **mat)
{
	int	y;

	y = 0;
	while (mat && mat[y])
	{
		ft_printf("%s\n", mat[y]);
		y++;
	}
}

/*int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return (1);
	ft_get_map(&map, av[1]);
	printf("NO -> '%s'\n", map.no_file);
	printf("SO -> '%s'\n", map.so_file);
	printf("WE -> '%s'\n", map.we_file);
	printf("EA -> '%s'\n", map.ea_file);
	printf("F  -> '%d'\n", map.floor_color);
	printf("C  -> '%d'\n", map.cieling_color);
	printf("width '%i'\n", map.width);
	printf("hight '%i'\n", map.hight);
	printf("player:\nx %i\ny %i\nv %c\n", map.player[0], map.player[1], (char) map.player[2]);
	ft_printmatrix(map.map);
}*/
