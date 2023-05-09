/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:22:41 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/06 16:00:11 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player *plr, t_map map)
{
	plr->posX = (double) map.player[X] + 0.5;
	plr->posY = (double) map.player[Y] + 0.5;
	if (map.player[Z] == 'N' || map.player[Z] == 'S')
	{
		plr->dirX = 1.0;
		plr->dirY = 0.0; //initial direction vector
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
		plr->dirY = 1.0; //initial direction vector
		plr->planeX = 0.66;
		plr->planeY = 0.0;
		if (map.player[Z] == 'W')
		{
			plr->dirY *= -1;
			plr->planeX *= -1;
		}
	}
}

void init_texture(t_texture *t, t_mlxvars meta, t_map map) //ancora da indirizzare le 4 immagini
{
	//check dei file?
	t->minimap = 0;
	t->imgs[0].img = mlx_xpm_file_to_image(meta.mlx, map.no_file, &t->texWidth, &t->texHeight);
	t->imgs[0].addr = mlx_get_data_addr(t->imgs[0].img, &t->imgs[0].bits_per_pixel, &t->imgs[0].line_length, &t->imgs[0].endian);
	t->imgs[1].img = mlx_xpm_file_to_image(meta.mlx, map.so_file, &t->texWidth, &t->texHeight);
	t->imgs[1].addr = mlx_get_data_addr(t->imgs[1].img, &t->imgs[1].bits_per_pixel, &t->imgs[1].line_length, &t->imgs[1].endian);
	t->imgs[2].img = mlx_xpm_file_to_image(meta.mlx, map.we_file, &t->texWidth, &t->texHeight);
	t->imgs[2].addr = mlx_get_data_addr(t->imgs[2].img, &t->imgs[2].bits_per_pixel, &t->imgs[2].line_length, &t->imgs[2].endian);
	t->imgs[3].img = mlx_xpm_file_to_image(meta.mlx, map.ea_file, &t->texWidth, &t->texHeight);
	t->imgs[3].addr = mlx_get_data_addr(t->imgs[3].img, &t->imgs[3].bits_per_pixel, &t->imgs[3].line_length, &t->imgs[3].endian);
}

int	main(int ac, char **av)
{
	t_mlxvars	meta;

	if (ac != 2)
		return (1);
	ft_get_map(&meta.map, av[1]);
//	ft_terminate(&meta);
	meta.mlx = mlx_init();
	meta.win = mlx_new_window(meta.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	//potremmo settarla a NULL e fare il destroy solo se not NULL
	meta.main.img = NULL;
	init_player(&meta.plr, meta.map);
	init_texture(&meta.tex, meta, meta.map);
	mlx_loop_hook(meta.mlx, big_draw, (void *)&meta);
	mlx_hook(meta.win, 2, 1L<<0, key_hooks, &meta);
	mlx_hook(meta.win, 17, 0L, ft_terminate, &meta);
	mlx_loop(meta.mlx);
	return(0);
}
