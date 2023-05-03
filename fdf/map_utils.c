/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:06:25 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 17:14:43 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_elem_atoi(t_map *map, int kx, int ky)
{
	static int	i = 0;

	while (map->map_memory[i] == 32 || map->map_memory[i] == '\n')
		i++;
	map->map[ky][kx].z = ft_atoi(&map->map_memory[i]);
	while (map->map_memory[i] >= '0' && map->map_memory[i] <= '9')
		i++;
	if (map->map_memory[i] == ',')
		map->map[ky][kx].col = ft_atoi_hex(&map->map_memory[i + 1]);
	else
		map->map[ky][kx].col = -1;
	while (map->map_memory[i] != 32 && map->map_memory[i] != 10
		&& map->map_memory[i])
		i++;
}

int	ft_popol_map(t_map *map)
{
	int	kx;
	int	ky;

	ky = 0;
	while (ky < map->y)
	{
		kx = 0;
		map->map[ky] = (t_dot *) ft_calloc(map->x, sizeof(t_dot));
		if (!map->map[ky])
			return (0);
		while (kx < map->x)
		{
			ft_elem_atoi(map, kx, ky);
			kx++;
		}
		ky++;
	}
	return (1);
}

int	ft_check_elem(char *line)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (line[i] == '-')
		i++;
	while (line[i] != 32 && line[i] != ',' && line[i] != '\n' && line[i] != 0)
	{
		if (line[i] < '0' || line[i] > '9')
			return (-1);
		i++;
	}
	if (line[i] != ',')
		return (i);
	if (!ft_ishex(&line[++i]))
		return (-1);
	while (line[i] != 32 && line[i] != '\n' && line[i] != '\0')
		i++;
	return (i);
}

int	ft_check_n_size_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (map->map_memory[i])
	{
		while (map->map_memory[i] == 32)
			i++;
		if (map->map_memory[i] == '\n' && map->map_memory[i + 1] == '\0')
			break ;
		if (map->map_memory[i] == '\n')
		{
			if (map->check_x != map->x)
				return (0);
			map->check_x = 0;
			map->y += 1;
			i++;
		}
		if (ft_check_elem(&map->map_memory[i++]) == -1)
			return (0);
		map->check_x += 1;
		while (map->map_memory[i] != 32 && map->map_memory[i] != '\n')
			i++;
	}
	return (1);
}
