/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:22:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/10 16:29:47 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*plr->dirY = 0.0; //initial direction vector */
void	init_player(t_player *plr, t_map map)
{
	plr->posX = (double) map.player[X] + 0.5001;
	plr->posY = (double) map.player[Y] + 0.5001;
	if (map.player[Z] == 'N' || map.player[Z] == 'S')
	{
		plr->dirX = 1.0;
		plr->dirY = 0.0;
		plr->planeX = 0.0;
		plr->planeY = 0.66;
		if (map.player[Z] == 'N')
			plr->dirX *= -1;
		else
			plr->planeY *= -1;
	}
	else
	{
		plr->dirX = 0.001;
		plr->dirY = 1.0;
		plr->planeX = 0.66;
		plr->planeY = 0.0;
		if (map.player[Z] == 'W')
		{
			plr->dirY *= -1;
			plr->planeX *= -1;
		}
	}
}

void	init_icon_texture(t_texture *t, t_mlxvars meta)
{
	t->plricon[0].img = mlx_xpm_file_to_image(meta.mlx,
			"pics/cow8.xpm", &t->icon8w, &t->icon8h);
	t->plricon[0].addr = mlx_get_data_addr(t->plricon[0].img,
			&t->plricon[0].bits_per_pixel, &t->plricon[0].line_length,
			&t->plricon[0].endian);
	t->plricon[1].img = mlx_xpm_file_to_image(meta.mlx,
			"pics/cow16.xpm", &t->icon16w, &t->icon16h);
	t->plricon[1].addr = mlx_get_data_addr(t->plricon[1].img,
			&t->plricon[1].bits_per_pixel, &t->plricon[1].line_length,
			&t->plricon[1].endian);
	t->plricon[2].img = mlx_xpm_file_to_image(meta.mlx,
			"pics/cow32.xpm", &t->icon32w, &t->icon32h);
	t->plricon[2].addr = mlx_get_data_addr(t->plricon[2].img,
			&t->plricon[2].bits_per_pixel, &t->plricon[2].line_length,
			&t->plricon[2].endian);
}

void	init_texture(t_texture *t, t_mlxvars meta, t_map map)
{
	init_icon_texture(t, meta);
	t->imgs[0].img = mlx_xpm_file_to_image(meta.mlx,
			map.no_file, &t->texWidth, &t->texHeight);
	t->imgs[0].addr = mlx_get_data_addr(t->imgs[0].img,
			&t->imgs[0].bits_per_pixel, &t->imgs[0].line_length,
			&t->imgs[0].endian);
	t->imgs[1].img = mlx_xpm_file_to_image(meta.mlx,
			map.so_file, &t->texWidth, &t->texHeight);
	t->imgs[1].addr = mlx_get_data_addr(t->imgs[1].img,
			&t->imgs[1].bits_per_pixel, &t->imgs[1].line_length,
			&t->imgs[1].endian);
	t->imgs[2].img = mlx_xpm_file_to_image(meta.mlx,
			map.we_file, &t->texWidth, &t->texHeight);
	t->imgs[2].addr = mlx_get_data_addr(t->imgs[2].img,
			&t->imgs[2].bits_per_pixel, &t->imgs[2].line_length,
			&t->imgs[2].endian);
	t->imgs[3].img = mlx_xpm_file_to_image(meta.mlx,
			map.ea_file, &t->texWidth, &t->texHeight);
	t->imgs[3].addr = mlx_get_data_addr(t->imgs[3].img,
			&t->imgs[3].bits_per_pixel, &t->imgs[3].line_length,
			&t->imgs[3].endian);
	t->pitch = 0;
	t->minimap = 0;
	t->mapf = -1;
}

int	main(int ac, char **av)
{
	t_mlxvars	meta;

	if (ac != 2)
		return (1);
	meta.mouse = false;
	ft_get_map(&meta.map, av[1]);
	meta.mlx = mlx_init();
	meta.win = mlx_new_window(meta.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	meta.main.img = NULL;
	init_player(&meta.plr, meta.map);
	init_texture(&meta.tex, meta, meta.map);
	mlx_hook(meta.win, 2, 1L << 0, key_hooks, &meta);
	mlx_hook(meta.win, 17, 0L, ft_terminate, &meta);
	mlx_hook(meta.win, 6, 1L << 6, ft_mouse_win3, (void *)&meta);
	mlx_hook(meta.win, 9, 1L << 21, focus_in, (void *)&meta);
	mlx_hook(meta.win, 10, 1L << 21, focus_out, (void *)&meta);
	mlx_loop_hook(meta.mlx, big_draw, (void *)&meta);
	mlx_loop(meta.mlx);
	return (0);
}
