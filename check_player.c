/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:01:18 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/06 13:47:53 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_isplayer(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

static void	ft_errorplayer(t_map *map, int z)
{
	static int	flag = 0;

	if (!flag && z == 1)
		flag = 1;
	else if ((!flag && z == 0) || (flag && z == 1))
		ft_exit_map(map, "The player must be one!\n");
}

void	ft_findplayer(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (ft_isplayer(map->map[y][x]))
			{
				ft_errorplayer(map, 1);
				map->player[0] = y;
				map->player[1] = x;
				map->player[2] = map->map[y][x];
			}
			x++;
		}
		y++;
	}
	ft_errorplayer(map, 0);
}
