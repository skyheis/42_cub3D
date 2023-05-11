/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_moving.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:20:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/11 15:36:10 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_mouse_move_b(int x, int y, double mouse_speed, t_mlxvars *meta)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = meta->plr.dirx;
	meta->plr.dirx = meta->plr.dirx * cos(mouse_speed)
		- meta->plr.diry * sin(mouse_speed);
	meta->plr.diry = old_dirx * sin(mouse_speed)
		+ meta->plr.diry * cos(mouse_speed);
	old_planex = meta->plr.planex;
	meta->plr.planex = meta->plr.planex * cos(mouse_speed)
		- meta->plr.planey * sin(mouse_speed);
	meta->plr.planey = old_planex * sin(mouse_speed)
		+ meta->plr.planey * cos(mouse_speed);
}

static void	ft_mouse_move_a(int x, int y, double mouse_speed, t_mlxvars *meta)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = meta->plr.dirx;
	meta->plr.dirx = meta->plr.dirx * cos(-mouse_speed)
		- meta->plr.diry * sin(-mouse_speed);
	meta->plr.diry = old_dirx * sin(-mouse_speed)
		+ meta->plr.diry * cos(-mouse_speed);
	old_planex = meta->plr.planex;
	meta->plr.planex = meta->plr.planex * cos(-mouse_speed)
		- meta->plr.planey * sin(-mouse_speed);
	meta->plr.planey = old_planex * sin(-mouse_speed)
		+ meta->plr.planey * cos(-mouse_speed);
}

int	ft_mouse_win3(int x, int y, void *p)
{
	t_mlxvars	*meta;
	double		mouse_speed;

	mouse_speed = 0.03;
	meta = (t_mlxvars *)p;
	mlx_mouse_hide(meta->mlx, meta->win);
	if (x > 540)
		ft_mouse_move_a(x, y, mouse_speed, meta);
	else if (x < WIN_WIDTH / 2)
		ft_mouse_move_b(x, y, mouse_speed, meta);
	if (y < WIN_HEIGHT / 2)
		meta->tex.pitch += 5;
	else if (y > WIN_HEIGHT / 2)
		meta->tex.pitch -= 5;
	return (0);
}
