/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ortographic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:23:05 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 17:15:36 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_orto_downright(t_mlxvars *meta, int *lim)
{
	t_dot	g;
	t_dot	h;

	g.col = 0x404040;
	h.col = 0x404040;
	g.x = lim[MINX];
	g.y = WIN_HEIGHT >> 1;
	h.x = (WIN_WIDE >> 1) + WIN_WIDE / 12;
	h.y = lim[MINY];
	ft_bresenham(meta, h, g);
	g.x = lim[MAXX];
	g.y = WIN_HEIGHT >> 1;
	h.x = (WIN_WIDE >> 1) + WIN_WIDE / 12;
	h.y = lim[MAXY];
	ft_bresenham(meta, h, g);
}

void	ft_orto_lines(t_mlxvars *meta)
{
	t_dot	a;
	t_dot	b;

	a.z = 0;
	a.col = -1;
	b.z = 0;
	b.col = -1;
	a.x = WIN_WIDE / 12 * 2;
	a.y = WIN_HEIGHT >> 1;
	b.x = WIN_WIDE;
	b.y = WIN_HEIGHT >> 1;
	ft_bresenham(meta, a, b);
	a.x = (WIN_WIDE >> 1) + WIN_WIDE / 12;
	a.y = 0;
	b.x = (WIN_WIDE >> 1) + WIN_WIDE / 12;
	b.y = WIN_HEIGHT;
	ft_bresenham(meta, a, b);
}

void	ft_ortographic_draw(t_mlxvars *meta, int k)
{
	int	new_zx;
	int	new_zy;

	new_zx = ((WIN_WIDE >> 2) + WIN_WIDE / 9);
	new_zy = (WIN_HEIGHT >> 2);
	ft_set_orto(meta->map, new_zx, new_zy, ft_top);
	ft_greyline_top(meta);
	ft_draw_map(meta, meta->map->map);
	new_zx = ((WIN_WIDE >> 2) + WIN_WIDE / 9);
	new_zy = (WIN_HEIGHT >> 1);
	ft_set_orto(meta->map, new_zx, new_zy + k, ft_ytoz);
	ft_greyline_down(meta);
	meta->map->minmax[MINY] = meta->map->min_y;
	meta->map->minmax[MAXY] = meta->map->max_y;
	ft_draw_map(meta, meta->map->map);
	new_zx = ((WIN_WIDE >> 1) + WIN_WIDE / 12);
	new_zy = (WIN_HEIGHT >> 2);
	ft_set_orto(meta->map, new_zx + k, new_zy, ft_xtoz);
	ft_greyline_right(meta);
	meta->map->minmax[MINX] = meta->map->min_x;
	meta->map->minmax[MAXX] = meta->map->max_x;
	ft_draw_map(meta, meta->map->map);
}

void	ft_ortographic(t_mlxvars *meta)
{
	int	new_zx;
	int	new_zy;
	int	k;
	int	old_zoom;

	old_zoom = meta->map->zoom;
	ft_orto_zoomfix(meta->map);
	new_zx = ((WIN_WIDE >> 2) + WIN_WIDE / 9);
	new_zy = (WIN_HEIGHT >> 1);
	k = check_zoomfit_down(meta->map, new_zx, new_zy, WIN_HEIGHT >> 2);
	ft_ortographic_draw(meta, k);
	ft_orto_downright(meta, meta->map->minmax);
	ft_orto_lines(meta);
	meta->map->zoom = old_zoom;
}
