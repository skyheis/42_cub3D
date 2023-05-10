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
		if(ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
			if (ray->rayDirX < 0)
				ray->dio = 0;
			else
				ray->dio = 1;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
			if (ray->rayDirY < 0)
				ray->dio = 2;
			else
				ray->dio = 3;
		}
		if(map->map[ray->mapX][ray->mapY] == '1')
			ray->hit = 1;
	}
}

/* calculate step and initial sideDist */
static void	ft_calc_step_side_dist(t_player *plr, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (plr->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - plr->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (plr->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - plr->posY) * ray->deltaDistY;
	}
}

/* - calculate ray position and direction */
/* - which box of the map we're in */
/* - length of ray from one x or y-side to next x or y-side */
void	ft_set_dda(int x, t_player *plr, t_ray *ray)
{
	ray->cameraX = 2 * x / (double)WIN_WIDTH - 1;
	ray->rayDirX = plr->dirX + plr->planeX * ray->cameraX;
	ray->rayDirY = plr->dirY + plr->planeY * ray->cameraX;
	ray->mapX = (int)plr->posX;
	ray->mapY = (int)plr->posY;
	if (ray->rayDirX == 0) 
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirX == 0) 
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	ft_calc_step_side_dist(plr, ray);
	ray->hit = 0;
}
