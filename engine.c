/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:53:59 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/09 14:48:40 by gfantech         ###   ########.fr       */
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

int big_draw(void *voidmeta)
{
	int			x;
	int			minizoom;
	t_mlxvars	*meta;
	double		frameTime;

	x = 0;
	mapf = -1;
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
	if (meta->tex.minimap)
		minizoom = ft_draw_minimap(meta, meta->map);
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
	if (minizoom >= 10)
		mlx_put_image_to_window(meta->mlx, meta->win, meta->tex.plricon[meta->tex.mapf].img, 42 + (int) (meta->plr.posY * zoom), 42 + (int) (meta->plr.posX * zoom));
	//print to text qua per gli fps
	return (0);
}
