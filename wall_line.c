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
			if (y < ((WIN_HEIGHT / 2) + meta->tex.pitch))
				my_mlx_pixel_put(&meta->main, x, y, map.cieling_color);
			else
				my_mlx_pixel_put(&meta->main, x, y, map.floor_color);
			x++;
		}
		y++;
	}
}

/* How much to increase the texture coordinate per screen pixel */
/* Starting texture coordinate */
/* while (Cast the texture coordinate to integer,
		and mask with (tex_height - 1) in case of overflow) */
/* 	if (ray->side == 0)
		tex_num = 0;
	else
		tex_num = 2; */
void	ft_draw_wall_line(int x, t_mlxvars *meta, t_ray *ray, t_texture *tex)
{
	int	y;
	int	color;

	tex->step = 1.0 * tex->tex_height / tex->line_height;
	tex->tex_pos = (tex->draw_start - tex->pitch - WIN_HEIGHT / 2
			+ tex->line_height / 2) * tex->step;
	y = tex->draw_start;
	while (y < tex->draw_end)
	{
		tex->tex_y = (int)tex->tex_pos & (tex->tex_height - 1);
		tex->tex_pos += tex->step;
		(void) ray;
		color = get_tex_color(tex, ray->dio);
		my_mlx_pixel_put(&meta->main, x, y, color);
		y++;
	}
}

/* Calculate distance of perpendicular ray
		(Euclidean distance would give fisheye effect!) */
/* Calculate height of line to draw on screen */
/* calculate lowest and highest pixel to fill in current stripe */
/* calculate value of wallx */
void	ft_calc_wall_ray(t_player *plr, t_ray *ray, t_texture *tex)
{
	if (ray->side == 0)
		ray->perp_walldist = (ray->side_distx - ray->delta_distx);
	else
		ray->perp_walldist = (ray->side_disty - ray->delta_disty);
	tex->line_height = (int)(WIN_HEIGHT / ray->perp_walldist);
	tex->draw_start = -tex->line_height / 2 + WIN_HEIGHT / 2 + tex->pitch;
	if (tex->draw_start < 0)
		tex->draw_start = 0;
	tex->draw_end = tex->line_height / 2 + WIN_HEIGHT / 2 + tex->pitch;
	if (tex->draw_end >= WIN_HEIGHT)
		tex->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		tex->wallx = plr->posy + ray->perp_walldist * ray->ray_diry;
	else
		tex->wallx = plr->posx + ray->perp_walldist * ray->ray_dirx;
	tex->wallx -= floor((tex->wallx));
	tex->tex_x = (int)(tex->wallx * (double)tex->tex_width);
	if ((ray->side == 0 && ray->ray_dirx > 0)
		|| (ray->side == 1 && ray->ray_diry < 0))
		tex->tex_x = tex->tex_width - tex->tex_x - 1;
}
