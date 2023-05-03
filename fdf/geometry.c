/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:04:39 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 16:10:08 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_ytoz(t_dot *dot, t_map *map)
{
	(void) map;
	dot->y = -dot->z * map->zoom / 2;
}

void	ft_xtoz(t_dot *dot, t_map *map)
{
	(void) map;
	dot->x = -dot->z * map->zoom / 2;
}

void	ft_top(t_dot *dot, t_map *map)
{
	(void) dot;
	(void) map;
}

void	ft_isometric(t_dot *dot, t_map *map)
{
	dot->x = (dot->x - dot->y) * cos(map->angle * M_PI / 180);
	dot->y = (dot->x + dot->y) * sin(map->angle * M_PI / 180)
		- (dot->z * map->zoom / 2);
}

void	ft_rotate_z(t_dot *dot, t_map *map)
{
	float	a;
	float	b;
	double	alpha;

	if (map->alpha == 0)
		return ;
	alpha = map->alpha * M_PI / 180;
	a = dot->x * cos(alpha) - dot->y * sin(alpha);
	b = dot->x * sin(alpha) + dot->y * cos(alpha);
	dot->x = a;
	dot->y = b;
}

/*void	ft_sphere(t_dot *dot, t_map *map)
{
	float x_norm;
	float y_norm;
	float theta;
	float phi;

	x_norm = dot->x / map->x;
	y_norm = dot->y / map->y;
	theta = y_norm * M_PI;
	phi = x_norm * 2 * M_PI;
	dot->x = ((map->x / (2 * M_PI) + 500) + dot->z) * sin(theta) * cos(phi);
	dot->y = ((map->x / (2 * M_PI) + 500) + dot->z) * sin(theta) * sin(phi);
}*/
