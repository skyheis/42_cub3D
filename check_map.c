/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:06:14 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/05 11:26:58 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_isvalidmap(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W' || c == '0')
		return (1);
	return (0);
}

static void	ft_iswallornot(t_map *map, char c)
{
	(void) map;
	if (c != '1' && c != 32)
		ft_exit_map(map, "Error: map is not closed or contains wrong char\n");
}

void	ft_fillflood(t_map *map, int x, int y)
{
	if (x == 0 || x == map->width)
		ft_iswallornot(map, map->map[y][x]);
	if (x < 0 || x >= map->width || y < 0 || y >= map->hight)
		return ;
	if (map->map[y][x] == '.' || map->map[y][x] == '1')
		return ;
	else if (ft_isvalidmap(map->map[y][x]))
		map->map[y][x] = '.';
	else
		ft_exit_map(map, "Error: map is not closed or contains wrong char\n");
	ft_fillflood(map, x + 1, y);
	ft_fillflood(map, x, y + 1);
	ft_fillflood(map, x - 1, y);
	ft_fillflood(map, x, y - 1);
}

void	ft_checkmap(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (map->map[y][x])
		ft_iswallornot(map, map->map[y][x++]);
	y = map->hight - 1;
	x = 0;
	while (map->map[y][x])
		ft_iswallornot(map, map->map[y][x++]);
	y = 1;
	while (y < map->hight - 1)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '0')
				ft_fillflood(map, x, y);
			x++;
		}
		y++;
	}
}
