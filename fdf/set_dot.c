/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:34:42 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 17:25:00 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_reset_minmax(t_map *map)
{
	map->min_x = WIN_WIDE;
	map->min_y = WIN_HEIGHT;
	map->max_x = -1;
	map->max_y = -1;
	return (0);
}

void	ft_fill_minmax(t_map *map, int the_x, int the_y)
{
	if (the_x > map->max_x)
		map->max_x = the_x;
	if (the_x < map->min_x)
		map->min_x = the_x;
	if (the_y > map->max_y)
		map->max_y = the_y;
	if (the_y < map->min_y)
		map->min_y = the_y;
}

void	ft_set_dot_utils(t_map *map, void (*ft_vision)(t_dot *, t_map *),
		int ky, int kx)
{
	ft_rotate_z(&map->map[ky][kx], map);
	ft_vision(&map->map[ky][kx], map);
	map->map[ky][kx].x += map->zx;
	map->map[ky][kx].y += map->zy;
	ft_fill_minmax(map, (int) map->map[ky][kx].x,
		(int) map->map[ky][kx].y);
}

int	ft_set_dot(t_map *map, void (*ft_vision)(t_dot *, t_map *))
{
	int	a;
	int	b;
	int	kx;
	int	ky;

	ky = ft_reset_minmax(map);
	b = -1 * (map->y / 2);
	while (ky < map->y)
	{
		kx = 0;
		a = -1 * (map->x / 2);
		while (kx < map->x)
		{
			map->map[ky][kx].x = (float)(a * map->zoom);
			map->map[ky][kx].y = (float)(b * map->zoom);
			ft_set_dot_utils(map, ft_vision, ky, kx);
			kx++;
			a++;
		}
		ky++;
		b++;
	}
	return (0);
}

void	ft_set_orto(t_map *map, int new_zx, int new_zy,
		void (*ft_vision)(t_dot *, t_map *))
{
	int	a;
	int	b;
	int	kx;
	int	ky;

	ky = ft_reset_minmax(map);
	b = -1 * (map->y / 2);
	while (ky < map->y)
	{
		kx = 0;
		a = -1 * (map->x / 2);
		while (kx < map->x)
		{
			map->map[ky][kx].x = (float)((a++) * map->zoom);
			map->map[ky][kx].y = (float)(b * map->zoom);
			ft_vision(&map->map[ky][kx], map);
			map->map[ky][kx].x += new_zx;
			map->map[ky][kx].y += new_zy;
			ft_fill_minmax(map, (int) map->map[ky][kx].x,
				(int) map->map[ky][kx].y);
			kx++;
		}
		ky++;
		b++;
	}
}

/*void	fdf_print_dot(t_map *maps, t_dot **mat)
{
		fdf_print_dot(map, map->map);
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < maps->y)
	{
		while (x < maps->x)
		{
			ft_printf("%i,%i,%i   ", mat[y][x].x, mat[y][x].y, mat[y][x].z);
			x++;
		}
		ft_printf("\n");
		y++;
		x = 0;
	}
}*/
