/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:59 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/10 10:10:01 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_reset_main_img(t_data *main, t_mlxvars meta)
{
	if (main->img)
		mlx_destroy_image(meta.mlx, main->img);
	main->img = mlx_new_image(meta.mlx, WIN_WIDTH, WIN_HEIGHT);
	main->addr = mlx_get_data_addr(main->img, &main->bits_per_pixel,
			&main->line_length, &main->endian);
}

void	ft_pickaxe(t_mlxvars *meta)
{
	int x;
	int y;
	int picx;
	int picy;
	int color;
	t_data barr;

	barr.img = mlx_xpm_file_to_image(meta->mlx, "pics/pickaxe256.xpm", &picx, &picy);
	barr.addr = mlx_get_data_addr(barr.img, &barr.bits_per_pixel, &barr.line_length, &barr.endian);
	y = 0;
	while (y < 256)
	{
		x = 0;
		while (x < 256)
		{
			color = *(int*) (barr.addr + (4 * picx  * x) + (4 * (int) y));
			if (color != 0x0)
				my_mlx_pixel_put(&meta->main, WIN_WIDTH - 256 + y, WIN_HEIGHT - 256 + x, color);
			x++;
		}
		y++;
	}
	mlx_destroy_image(meta->mlx, barr.img);
}

int big_draw(void *voidmeta)
{
	int			x;
	t_mlxvars	*meta;
	double		frameTime;

	x = 0;
	meta = (t_mlxvars *)voidmeta;
	ft_reset_main_img(&meta->main, *meta);
	ft_draw_cieiling_floor(meta, meta->map);
	while (x < WIN_WIDTH)
	{
		ft_set_dda(x, &meta->plr, &meta->ray);
		ft_perform_dda(&meta->ray, &meta->map);

		ft_calc_wall_ray(&meta->plr, &meta->ray, &meta->tex);
		ft_draw_wall_line(x, meta, &meta->ray, &meta->tex);

		x++;
	}

	ft_pickaxe(meta);

	//timing for input and FPS counter
	meta->ray.oldTime = meta->ray.time;
	meta->ray.time = get_time();
	frameTime = (meta->ray.time - meta->ray.oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
	//speed modifiers
//	printf("frameTime: %f\n", frameTime);
	//meta->plr.moveSpeed = frameTime * 10.0; //the constant value is in squares/second
	//meta->plr.rotSpeed = frameTime * 8.0; //the constant value is in radians/second
	(void) frameTime;
	meta->plr.moveSpeed = 0.1; //the constant value is in squares/second
	meta->plr.rotSpeed = 0.09; //the constant value is in radians/second
	mlx_put_image_to_window(meta->mlx, meta->win, meta->main.img, 0,0);
	if (meta->tex.minimap)
		ft_draw_minimap(meta, meta->map);
	return (0);
}
