/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:20:24 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 17:12:59 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_WIDE || x <= 0 || y >= WIN_HEIGHT || y <= 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	ft_bresenham(t_mlxvars *meta, t_dot one, t_dot two)
{
	float	step;
	float	dx;
	float	dy;

	dx = two.x - one.x;
	dy = two.y - one.y;
	if (fabsf(dx) > fabsf(dy))
		step = fabsf(dx);
	else
		step = fabsf(dy);
	dx = dx / step;
	dy = dy / step;
	while ((int)(one.x - two.x) || (int)(one.y - two.y))
	{
		my_mlx_pixel_put(meta->img, one.x, one.y, one.col);
		one.x += dx;
		one.y += dy;
		if (one.x < 0 || one.y < 0)
			break ;
		if (one.x > WIN_WIDE || one.y > WIN_HEIGHT)
			break ;
	}
}

void	ft_draw_map(t_mlxvars *meta, t_dot **map)
{
	int	kx;
	int	ky;

	ky = 0;
	(void) map;
	while (ky < meta->map->y)
	{
		kx = 0;
		while (kx < meta->map->x)
		{
			my_mlx_pixel_put(meta->img, (int) map[ky][kx].x,
				(int) map[ky][kx].y, map[ky][kx].col);
			if (kx < meta->map->x - 1)
				ft_bresenham(meta, map[ky][kx], map[ky][kx + 1]);
			if (ky < meta->map->y - 1)
				ft_bresenham(meta, map[ky][kx], map[ky + 1][kx]);
			kx++;
		}
		ky++;
	}
}
