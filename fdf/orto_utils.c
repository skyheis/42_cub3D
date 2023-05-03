/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orto_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:36:32 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 14:37:08 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	ft_orto_minxdot(t_map *map)
{
	int	kx;
	int	ky;

	ky = 0;
	while (ky < map->y)
	{
		kx = 0;
		while (kx < map->x)
		{
			if (map->map[ky][kx].x == map->min_x)
				return (map->map[ky][kx]);
			kx++;
		}
		ky++;
	}
	return (map->map[ky][kx]);
}

t_dot	ft_orto_minydot(t_map *map)
{
	int	kx;
	int	ky;

	ky = 0;
	while (ky < map->y)
	{
		kx = 0;
		while (kx < map->x)
		{
			if (map->map[ky][kx].y == map->min_y)
				return (map->map[ky][kx]);
			kx++;
		}
		ky++;
	}
	return (map->map[ky][kx]);
}

void	ft_greyline_right(t_mlxvars *meta)
{
	t_dot	g;
	t_dot	h;

	g.col = 0x404040;
	g.x = meta->map->min_x;
	g.y = WIN_HEIGHT >> 1;
	h = ft_orto_minxdot(meta->map);
	h.col = 0x404040;
	ft_bresenham(meta, h, g);
	g.x = meta->map->max_x;
	h.x = meta->map->max_x;
	ft_bresenham(meta, h, g);
	g.x = (WIN_WIDE >> 1) + WIN_WIDE / 12;
	g.y = meta->map->max_y;
	h.y = meta->map->max_y;
	ft_bresenham(meta, h, g);
	h = ft_orto_minydot(meta->map);
	h.col = 0x404040;
	g.y = meta->map->min_y;
	ft_bresenham(meta, h, g);
}

void	ft_greyline_down(t_mlxvars *meta)
{
	t_dot	g;
	t_dot	h;

	g.col = 0x404040;
	h.col = 0x404040;
	g.x = meta->map->min_x;
	g.y = WIN_HEIGHT >> 1;
	h.x = meta->map->min_x;
	h.y = meta->map->max_y;
	ft_bresenham(meta, h, g);
	g.x = meta->map->max_x;
	h.x = meta->map->max_x;
	ft_bresenham(meta, h, g);
	g.x = (WIN_WIDE >> 1) + WIN_WIDE / 12;
	g.y = meta->map->max_y;
	h.y = meta->map->max_y;
	ft_bresenham(meta, h, g);
	h = ft_orto_minydot(meta->map);
	h.col = 0x404040;
	g.y = meta->map->min_y;
	ft_bresenham(meta, h, g);
}

void	ft_greyline_top(t_mlxvars *meta)
{
	t_dot	g;
	t_dot	h;

	g.col = 0x404040;
	h.col = 0x404040;
	g.x = meta->map->min_x;
	g.y = WIN_HEIGHT >> 1;
	h.x = meta->map->min_x;
	h.y = meta->map->max_y;
	ft_bresenham(meta, h, g);
	g.x = meta->map->max_x;
	h.x = meta->map->max_x;
	ft_bresenham(meta, h, g);
	g.x = (WIN_WIDE >> 1) + WIN_WIDE / 12;
	g.y = meta->map->max_y;
	h.y = meta->map->max_y;
	ft_bresenham(meta, h, g);
	g.y = meta->map->min_y;
	h.y = meta->map->min_y;
	ft_bresenham(meta, h, g);
}
