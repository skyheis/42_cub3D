/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:51:06 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 17:10:30 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_menu_mid(t_mlxvars *meta);
void	ft_menu_bot_one(t_mlxvars *meta);
void	ft_menu_bot_two(t_mlxvars *meta);
void	ft_menu_helper(t_mlxvars *meta);

void	ft_menu_top(t_mlxvars *meta)
{
	mlx_string_put(meta->mlx, meta->win, 42, 42 + (30 * 0), 0xFFFF0000,
		"============= FdF ggiannit =============");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 1), -1,
		"Keymap");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 2), -1,
		"move map:       WASD");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 3), -1,
		"zoom in:        +  || rot_up");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 4), -1,
		"zoom out:       -  || rot_down");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 5), -1,
		"rotate z +5:    Q  ||  E");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 6), -1,
		"rotate z +90:    R");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 7), -1,
		"iso angle +5:   Z  ||  X");
	ft_menu_mid(meta);
}

void	ft_menu_mid(t_mlxvars *meta)
{
	mlx_string_put(meta->mlx, meta->win, 42, 42 + (30 * 9), 0xFFFFFF00,
		"============== Projections =============");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 10), -1,
		"press 1:   isometric");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 11), -1,
		"press 2:   orthographic");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 12), -1,
		"press 8:   down side view");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 13), -1,
		"press 9:   right side view");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 14), -1,
		"press 0:   top view");
	ft_menu_bot_one(meta);
}

void	ft_menu_bot_one(t_mlxvars *meta)
{
	char	*str;

	mlx_string_put(meta->mlx, meta->win, 42, 42 + (30 * 16), 0xFF0000FF,
		"============== Map's  info =============");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 17), -1,
		"num of lines:");
	str = ft_itoa(meta->map->x);
	mlx_string_put(meta->mlx, meta->win, 82 + 142, 42 + (30 * 17), 65535, str);
	ft_free_null(&str);
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 18), -1,
		"num of colums:");
	str = ft_itoa(meta->map->y);
	mlx_string_put(meta->mlx, meta->win, 82 + 142, 42 + (30 * 18), 65535, str);
	ft_free_null(&str);
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 19), -1,
		"map center x:");
	str = ft_itoa(meta->map->zx);
	mlx_string_put(meta->mlx, meta->win, 82 + 142, 42 + (30 * 19), 65535, str);
	ft_free_null(&str);
	ft_menu_bot_two(meta);
}

void	ft_menu_bot_two(t_mlxvars *meta)
{
	char	*str;

	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 20), -1,
		"map center y:");
	str = ft_itoa(meta->map->zy);
	mlx_string_put(meta->mlx, meta->win, 82 + 142, 42 + (30 * 20), 65535, str);
	ft_free_null(&str);
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 21), -1,
		"map zoom:");
	str = ft_itoa(meta->map->zoom);
	mlx_string_put(meta->mlx, meta->win, 82 + 142, 42 + (30 * 21), 65535, str);
	ft_free_null(&str);
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 22), -1,
		"z's angle:");
	str = ft_itoa(meta->map->alpha);
	mlx_string_put(meta->mlx, meta->win, 82 + 142, 42 + (30 * 22), 65535, str);
	ft_free_null(&str);
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 23), -1,
		"iso's angle:");
	str = ft_itoa(meta->map->angle);
	mlx_string_put(meta->mlx, meta->win, 82 + 142, 42 + (30 * 23), 65535, str);
	ft_free_null(&str);
	ft_menu_helper(meta);
}

void	ft_menu_helper(t_mlxvars *meta)
{
	mlx_string_put(meta->mlx, meta->win, 42, 42 + (30 * 26), 0xFFFF00FF,
		"============= Thanks to... =============");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 27), -1,
		"gfantec");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 28), -1,
		"naal-jen");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 29), -1,
		"ncortigi");
	mlx_string_put(meta->mlx, meta->win, 82, 42 + (30 * 30), -1,
		"ailopez-");
}
