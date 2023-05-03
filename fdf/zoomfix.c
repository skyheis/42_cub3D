/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoomfix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:54:33 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 10:56:19 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_zoom_td(t_map *map)
{
	int	diff_y;

	map->zoom = (WIN_WIDE - (WIN_WIDE / 10)) / (map->x);
	ft_set_dot(map, ft_isometric);
	while (map->min_x < map->minmax[MINX] || map->max_x > map->minmax[MAXX])
	{
		map->zoom -= 1;
		ft_set_dot(map, ft_isometric);
	}
	while (map->min_y < map->minmax[MINY])
	{
		diff_y = abs(map->min_y - map->minmax[MINY]);
		if (diff_y + map->max_y < map->minmax[MAXY])
			map->zy += diff_y;
		else
			map->zoom -= 1;
		ft_set_dot(map, ft_isometric);
	}
}

void	ft_orto_zoomfix(t_map *map)
{
	int	zoom_x;
	int	zoom_y;
	int	new_wide;

	new_wide = WIN_WIDE - (WIN_WIDE / 6);
	zoom_x = ((new_wide >> 1) - ((new_wide >> 1) / 10)) / map->x;
	zoom_y = ((WIN_HEIGHT >> 1) - ((WIN_HEIGHT >> 1) / 10)) / map->y;
	if (zoom_x > zoom_y)
		map->zoom = zoom_y;
	else
		map->zoom = zoom_x;
	if (!map->zoom)
		map->zoom = 1;
}

int	check_zoomfit_down(t_map *map, int new_zx, int new_zy, int k)
{
	int	diff_y;

	ft_set_orto(map, new_zx, new_zy + k, ft_ytoz);
	while (map->min_y < new_zy + 15 || map->max_y > WIN_HEIGHT - 15)
	{
		diff_y = abs(map->min_y - new_zy - 15);
		if (diff_y + map->max_y < WIN_HEIGHT - 15)
			k += diff_y;
		else
			map->zoom -= 1;
		ft_set_orto(map, new_zx, new_zy + k, ft_ytoz);
	}
	return (k);
}
