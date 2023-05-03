/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:36:35 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 17:14:14 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_map_x(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_memory[i] != '\n')
	{
		while (map->map_memory[i] == 32)
			i++;
		if (map->map_memory[i] != '\n')
			map->x += 1;
		while (map->map_memory[i] != 32 && map->map_memory[i] != '\n')
			i++;
	}
}

int	ft_read_map(t_map *map, char *file)
{
	int		fd;
	int		b_readed;
	char	*file_memory;

	b_readed = READ_SIZE;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while (b_readed == READ_SIZE)
	{
		file_memory = (char *) ft_calloc(READ_SIZE + 1, sizeof(char));
		b_readed = read(fd, file_memory, READ_SIZE);
		if (b_readed == -1)
			return (0);
		map->map_memory = ft_strjoin_free(map->map_memory, file_memory);
	}
	close(fd);
	ft_set_map_x(map);
	return (1);
}

int	ft_check_infile(char *infile)
{
	int	len;

	len = ft_strlen(infile);
	if (len < 5)
		return (0);
	if (!ft_strncmp(&infile[len - 4], ".fdf", 5))
		return (1);
	return (0);
}

void	ft_init_map(t_map *map)
{
	map->map_memory = NULL;
	map->map = NULL;
	map->x = 0;
	map->y = 1;
	map->check_x = 0;
	map->zoom = 1;
	map->angle = 60;
	map->alpha = -90;
	map->beta = 0;
	map->gamma = 0;
	map->vision = 1;
	map->zx = (WIN_WIDE >> 1) + WIN_WIDE / 12;
	map->zy = WIN_HEIGHT >> 1;
	map->min_x = WIN_WIDE;
	map->min_y = WIN_HEIGHT;
	map->max_x = -1;
	map->max_y = -1;
	map->minmax = (int *) ft_calloc(4, sizeof(int));
	map->minmax[MINX] = WIN_WIDE / 18;
	map->minmax[MINY] = WIN_HEIGHT / 18;
	map->minmax[MAXX] = WIN_WIDE - map->minmax[MINX];
	map->minmax[MAXY] = WIN_HEIGHT - map->minmax[MINY];
}

t_map	*ft_get_map(char **av)
{
	t_map	*map;

	if (!ft_check_infile(av[1]))
		return (NULL);
	map = (t_map *) ft_calloc(1, sizeof(t_map));
	ft_init_map(map);
	if (!map)
		return (NULL);
	if (!ft_read_map(map, av[1]))
		return (ft_free_null((char **)&map));
	if (!ft_check_n_size_map(map))
		return (NULL);
	map->map = (t_dot **) ft_calloc(map->y, sizeof(t_dot *));
	if (!map->map)
		return (NULL);
	if (!ft_popol_map(map))
		return (NULL);
	ft_free_null(&map->map_memory);
	return (map);
}

/* printf("x is %d\ny is %d\n", map->x, map->y); */

/*void	fdf_print_matrix(t_map *maps, t_dot **mat)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < maps->y)
	{
		while (x < maps->x)
		{
			ft_printf("%i,%i ", mat[y][x].z, mat[y][x].col);
			x++;
		}
		ft_printf("\n");
		y++;
		x = 0;
	}
}*/

/*int	main(int ac, char **av)
{
	t_map	*map;

	if (ac < 2)
		return (1);
	map = ft_get_map(av);
if (!map)
		return (2);
	printf("x is %d\ny is %d\n", map->x, map->y);
	//fdf_print_matrix(map, map->map);
	//write(1, "\n", 1);
	//fdf_print_matrix(map, map->col);
	ft_free_map(map);
	return (0);
}*/
