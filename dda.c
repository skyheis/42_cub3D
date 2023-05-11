/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:48:28 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/10 15:18:13 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* - jump to next map square, either in x-direction, or in y-direction */
/* - Check if ray has hit a wall */
void	ft_perform_dda(t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->mapx += ray->step_x;
			ray->side = 0;
			if (ray->ray_dirx < 0)
				ray->dio = 0;
			else
				ray->dio = 1;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->mapy += ray->step_y;
			ray->side = 1;
			if (ray->ray_diry < 0)
				ray->dio = 2;
			else
				ray->dio = 3;
		}
		if (map->map[ray->mapx][ray->mapy] == '1')
			ray->hit = 1;
	}
}

/* calculate step and initial sideDist */
static void	ft_calc_step_side_dist(t_player *plr, t_ray *ray)
{
	if (ray->ray_dirx < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (plr->posx - ray->mapx) * ray->delta_distx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->mapx + 1.0 - plr->posx) * ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (plr->posy - ray->mapy) * ray->delta_disty;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->mapy + 1.0 - plr->posy) * ray->delta_disty;
	}
}

/* - calculate ray position and direction */
/* - which box of the map we're in */
/* - length of ray from one x or y-side to next x or y-side */
void	ft_set_dda(int x, t_player *plr, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dirx = plr->dirx + plr->planex * ray->camera_x;
	ray->ray_diry = plr->diry + plr->planey * ray->camera_x;
	ray->mapx = (int)plr->posx;
	ray->mapy = (int)plr->posy;
	if (ray->ray_dirx == 0)
		ray->delta_distx = 1e30;
	else
		ray->delta_distx = fabs(1 / ray->ray_dirx);
	if (ray->ray_dirx == 0)
		ray->delta_disty = 1e30;
	else
		ray->delta_disty = fabs(1 / ray->ray_diry);
	ft_calc_step_side_dist(plr, ray);
	ray->hit = 0;
}
