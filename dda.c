/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:48:28 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/06 17:51:23 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_perform_dda(t_player *plr, t_ray *ray, t_map *map)
{
	//perform DDA
	(void) plr;
	ray->hit = 0; //was there a wall hit?
	while (ray->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0; //muro x
			if (ray->rayDirX < 0)// && !ray->rayDirY
				ray->dio = 0; //muro x
			else
				ray->dio = 1; //muro x
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1; //muro x
			if (ray->rayDirY < 0)// && !ray->rayDirY
				ray->dio = 2; //muro x
			else
				ray->dio = 3; //muro x
		}
		//Check if ray has hit a wall
		if(map->map[ray->mapX][ray->mapY] == '1') //is 1
			ray->hit = 1;
	}
}

static void	ft_calc_step_side_dist(t_player *plr, t_ray *ray)
{
	//calculate step and initial sideDist
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

void	ft_set_dda(int x, t_player *plr, t_ray *ray)
{
	//calculate ray position and direction
	//ray->cameraX = 2 * x / (double)WIN_WIDTH - 1; //x-coordinate in camera space
	ray->cameraX = 2 * x / (double)WIN_WIDTH - 1; //x-coordinate in camera space
	ray->rayDirX = plr->dirX + plr->planeX * ray->cameraX;
	ray->rayDirY = plr->dirY + plr->planeY * ray->cameraX;
	//printf("rayDirX %f\nrayDirY %f\n", ray->rayDirX, ray->rayDirY);
	//printf("plrDirX %f\nplrDirY %f\n", plr->dirX, plr->dirY);
	//printf("planeX %f\nplaneY %f\n\n", plr->planeX, plr->planeY);
	//which box of the map we're in
	ray->mapX = (int)plr->posX;
	ray->mapY = (int)plr->posY;
	//length of ray from one x or y-side to next x or y-side
	if (ray->rayDirX == 0) 
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirX == 0) 
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	ft_calc_step_side_dist(plr, ray);
}
