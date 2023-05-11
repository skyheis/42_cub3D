/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:48:28 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/10 15:18:13 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_terminate(t_mlxvars *meta)
{
	if (meta->main.img)
		mlx_destroy_image(meta->mlx, meta->main.img);
	if (meta->tex.imgs[0].img)
		mlx_destroy_image(meta->mlx, meta->tex.imgs[0].img);
	if (meta->tex.imgs[1].img)
		mlx_destroy_image(meta->mlx, meta->tex.imgs[1].img);
	if (meta->tex.imgs[2].img)
		mlx_destroy_image(meta->mlx, meta->tex.imgs[2].img);
	if (meta->tex.imgs[3].img)
		mlx_destroy_image(meta->mlx, meta->tex.imgs[3].img);
	if (meta->tex.plricon[0].img)
		mlx_destroy_image(meta->mlx, meta->tex.plricon[0].img);
	if (meta->tex.plricon[1].img)
		mlx_destroy_image(meta->mlx, meta->tex.plricon[1].img);
	if (meta->tex.plricon[2].img)
		mlx_destroy_image(meta->mlx, meta->tex.plricon[2].img);
	if (meta->win)
		mlx_destroy_window(meta->mlx, meta->win);
	if (meta->mlx)
		mlx_destroy_display(meta->mlx);
	ft_free_null((char **) &meta->mlx);
	ft_exit_map(&meta->map, NULL);
	exit(0);
}

void	ft_exit_map(t_map *map, char *str)
{
	ft_free_null(&map->no_file);
	ft_free_null(&map->so_file);
	ft_free_null(&map->we_file);
	ft_free_null(&map->ea_file);
	ft_free_null(&map->map_memory);
	ft_free_matrix(&map->map);
	ft_putstr_fd(str, 2);
	exit(1);
}
