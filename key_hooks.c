/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:20:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/10 15:36:10 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* both camera direction and camera plane must be rotated */
void	ft_rotate_cam_l(int keycode, t_player *plr)
{
	double	old_dirx;
	double	old_planex;

	if (keycode == LEFT)
	{
		old_dirx = plr->dirx;
		plr->dirx = plr->dirx * cos(plr->rot_speed)
			- plr->diry * sin(plr->rot_speed);
		plr->diry = old_dirx * sin(plr->rot_speed)
			+ plr->diry * cos(plr->rot_speed);
		old_planex = plr->planex;
		plr->planex = plr->planex * cos(plr->rot_speed)
			- plr->planey * sin(plr->rot_speed);
		plr->planey = old_planex * sin(plr->rot_speed)
			+ plr->planey * cos(plr->rot_speed);
	}
}

/* both camera direction and camera plane must be rotated */
void	ft_rotate_cam_r(int keycode, t_player *plr)
{
	double	old_dirx;
	double	old_planex;

	if (keycode == RIGHT)
	{
		old_dirx = plr->dirx;
		plr->dirx = plr->dirx * cos(-plr->rot_speed)
			- plr->diry * sin(-plr->rot_speed);
		plr->diry = old_dirx * sin(-plr->rot_speed)
			+ plr->diry * cos(-plr->rot_speed);
		old_planex = plr->planex;
		plr->planex = plr->planex * cos(-plr->rot_speed)
			- plr->planey * sin(-plr->rot_speed);
		plr->planey = old_planex * sin(-plr->rot_speed)
			+ plr->planey * cos(-plr->rot_speed);
	}
}

void	ft_change_pitch(int keycode, t_texture *tex)
{
	if (keycode == UP)
		tex->pitch += 30;
	else if (keycode == DOWN)
		tex->pitch -= 30;
}

int	key_hooks(int keycode, t_mlxvars *meta)
{
	t_player	*plr;

	plr = &meta->plr;
	if (keycode == TAB_KEY)
	{
		if (meta->tex.minimap)
			meta->tex.minimap = 0;
		else
			meta->tex.minimap = 1;
	}
	if (keycode == B_ESC)
		ft_terminate(meta);
	ft_move_plr_fb(keycode, plr, meta);
	ft_move_plr_lr(keycode, plr, meta);
	ft_rotate_cam_r(keycode, plr);
	ft_rotate_cam_l(keycode, plr);
	ft_change_pitch(keycode, &meta->tex);
	return (0);
}
