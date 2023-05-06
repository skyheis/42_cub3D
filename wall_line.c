/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:17:29 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/06 17:55:01 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_cieiling_floor(t_mlxvars *meta, t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT - 1)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)//100 * 64)
				my_mlx_pixel_put(&meta->main, x, y, map.cieling_color);
			else
				my_mlx_pixel_put(&meta->main, x, y, map.floor_color);
			x++;
		}
		y++;
	}
}

void	ft_draw_wall_line(int x, t_mlxvars *meta, t_ray *ray, t_texture *tex)
{
	int	y;
	int	tex_num;
	int	color;

	// How much to increase the texture coordinate per screen pixel
	tex->step = 1.0 * tex->texHeight / tex->lineHeight;
	// Starting texture coordinate
	tex->texPos = (tex->drawStart - tex->pitch - WIN_HEIGHT / 2 + tex->lineHeight / 2) * tex->step;
	//piu che tex_num e' side N E S W
	if (ray->side == 0)
		tex_num = 0;
	else
		tex_num = 2;
	(void) tex_num;
	//tex_num = meta.map.map[ray->mapX][ray->mapY];
	y = tex->drawStart;
	while (y < tex->drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		tex->texY = (int)tex->texPos & (tex->texHeight - 1);
		tex->texPos += tex->step;
		//color = get_tex_color(tex, tex_num);
		(void) ray;
		color = get_tex_color(tex, ray->dio);// ray->sidewall);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		//if(ray->side == 1)
		//	color = (color >> 1) & 8355711;
	 	my_mlx_pixel_put(&meta->main, x, y, color);
		y++;
	}
}

void	ft_calc_wall_ray(t_player *plr, t_ray *ray, t_texture *tex)
{
	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	//Calculate height of line to draw on screen
	tex->lineHeight = (int)(WIN_HEIGHT / ray->perpWallDist);
	tex->pitch = 0; //provo a cambiarlo e vedo cosa cambia lol
	//calculate lowest and highest pixel to fill in current stripe
	tex->drawStart = -tex->lineHeight / 2 + WIN_HEIGHT / 2 + tex->pitch;
	if (tex->drawStart < 0)
		tex->drawStart = 0;
	tex->drawEnd = tex->lineHeight / 2 + WIN_HEIGHT / 2 + tex->pitch;
	if(tex->drawEnd >= WIN_HEIGHT)
		tex->drawEnd = WIN_HEIGHT - 1;
	//calculate value of wallX
	if(ray->side == 0)
		tex->wallX = plr->posY + ray->perpWallDist * ray->rayDirY;
	else
		tex->wallX = plr->posX + ray->perpWallDist * ray->rayDirX;
	tex->wallX -= floor((tex->wallX));
	//x coordinate on the texture
	tex->texX = (int)(tex->wallX * (double)tex->texWidth);
	if ((ray->side == 0 && ray->rayDirX > 0)
			|| (ray->side == 1 && ray->rayDirY < 0))
		tex->texX = tex->texWidth - tex->texX - 1; //ma sono ugauli
}
