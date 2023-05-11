/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:18:21 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/10 15:24:19 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_base(t_mlxvars *meta, t_map map, int zoom)
{
	int	x;
	int	y;

	x = 0;
	while (x / zoom < map.hight)
	{
		y = 0;
		while (y / zoom < map.width)
		{
			if (map.map[x / zoom][y / zoom] == '1')
				my_mlx_pixel_put(&meta->main, 42 + y, 42 + x, 0x0000FF);
			else if (map.map[x / zoom][y / zoom] == '.')
				my_mlx_pixel_put(&meta->main, 42 + y, 42 + x, 0xFFFFFF);
			y += 2;
		}
		x += 2;
	}
}

static void	ft_dram_miniicon(t_mlxvars *meta, int zoom)
{
	my_mlx_pixel_put(&meta->main, 41 + (int)(meta->plr.posY * zoom),
		41 + (int)(meta->plr.posX * zoom), 0x00FF00);
	if (zoom > 3)
	{
		my_mlx_pixel_put(&meta->main, 42 + (int)(meta->plr.posY * zoom),
			41 + (int)(meta->plr.posX * zoom), 0x00FF00);
		my_mlx_pixel_put(&meta->main, 41 + (int)(meta->plr.posY * zoom),
			42 + (int)(meta->plr.posX * zoom), 0x00FF00);
		my_mlx_pixel_put(&meta->main, 42 + (int)(meta->plr.posY * zoom),
			42 + (int)(meta->plr.posX * zoom), 0x00FF00);
	}
}

int	ft_draw_minimap(t_mlxvars *meta, t_map map)
{
	int	zoom;

	zoom = 1;
	while (map.hight * zoom < WIN_HEIGHT - 84
		&& map.width * zoom < WIN_WIDTH - 48)
		zoom++;
	ft_draw_base(meta, map, zoom);
	if (zoom < 10)
		ft_dram_miniicon(meta, zoom);
	else if (zoom < 15)
		mlx_put_image_to_window(meta->mlx, meta->win, meta->tex.plricon[0].img,
			38 + (int)(meta->plr.posY * zoom),
			38 + (int)(meta->plr.posX * zoom));
	else if (zoom < 20)
		mlx_put_image_to_window(meta->mlx, meta->win, meta->tex.plricon[1].img,
			34 + (int)(meta->plr.posY * zoom),
			34 + (int)(meta->plr.posX * zoom));
	else
		mlx_put_image_to_window(meta->mlx, meta->win, meta->tex.plricon[2].img,
			26 + (int)(meta->plr.posY * zoom),
			26 + (int)(meta->plr.posX * zoom));
	return (zoom);
}
