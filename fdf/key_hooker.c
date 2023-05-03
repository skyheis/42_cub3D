/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:00:08 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 17:13:51 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_if_close_x(t_mlxvars *meta)
{
	ft_clean_all(meta);
	exit(0);
	return (0);
}

void	ft_key_press_one(int key_code, t_mlxvars *meta)
{
	if (key_code == W_KEY)
		meta->map->zy -= 20;
	else if (key_code == A_KEY)
		meta->map->zx -= 20;
	else if (key_code == S_KEY)
		meta->map->zy += 20;
	else if (key_code == D_KEY)
		meta->map->zx += 20;
	else if (key_code == Z_KEY)
		meta->map->angle += 5;
	else if (key_code == X_KEY)
		meta->map->angle -= 5;
	else if (key_code == KZERO)
		meta->map->vision = 0;
	else if (key_code == KOTTO)
		meta->map->vision = 8;
	else if (key_code == KNINE)
		meta->map->vision = 9;
	else if (key_code == KONE)
		meta->map->vision = 1;
	else if (key_code == KTWO)
		meta->map->vision = 2;
}

int	ft_key_press(int key_code, t_mlxvars *meta)
{
	if (key_code == MAG_KEY || key_code == ROT_UP)
		meta->map->zoom += 1;
	else if (key_code == MIN_KEY || key_code == ROT_DOWN)
		meta->map->zoom -= 1;
	else if (key_code == B_ESC)
	{
		ft_clean_all(meta);
		exit(0);
	}
	else if (key_code == R_KEY)
	{
		if (meta->map->alpha != 0 && (meta->map->alpha % 90) != 0)
			meta->map->alpha = 90;
		else
			meta->map->alpha -= 90;
	}
	else if (key_code == E_KEY)
		meta->map->alpha -= 5;
	else if (key_code == Q_KEY)
		meta->map->alpha += 5;
	else
		ft_key_press_one(key_code, meta);
	ft_set_img(meta, meta->img);
	ft_menu_top(meta);
	return (0);
}

int	ft_mouse_press(int key_code, int x, int y, t_mlxvars *meta)
{
	(void) x;
	(void) y;
	if (key_code == ROT_UP)
		meta->map->zoom += 1;
	else if (key_code == ROT_DOWN)
		meta->map->zoom -= 1;
	ft_set_img(meta, meta->img);
	ft_menu_top(meta);
	return (0);
}
