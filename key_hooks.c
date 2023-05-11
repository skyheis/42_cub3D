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
	double	oldDirX;
	double	oldPlaneX;

	if (keycode == LEFT)
	{
		oldDirX = plr->dirX;
		plr->dirX = plr->dirX * cos(plr->rotSpeed)
			- plr->dirY * sin(plr->rotSpeed);
		plr->dirY = oldDirX * sin(plr->rotSpeed)
			+ plr->dirY * cos(plr->rotSpeed);
		oldPlaneX = plr->planeX;
		plr->planeX = plr->planeX * cos(plr->rotSpeed)
			- plr->planeY * sin(plr->rotSpeed);
		plr->planeY = oldPlaneX * sin(plr->rotSpeed)
			+ plr->planeY * cos(plr->rotSpeed);
	}
}

/* both camera direction and camera plane must be rotated */
void	ft_rotate_cam_r(int keycode, t_player *plr)
{
	double	oldDirX;
	double	oldPlaneX;

	if (keycode == RIGHT)
	{
		oldDirX = plr->dirX;
		plr->dirX = plr->dirX * cos(-plr->rotSpeed)
			- plr->dirY * sin(-plr->rotSpeed);
		plr->dirY = oldDirX * sin(-plr->rotSpeed)
			+ plr->dirY * cos(-plr->rotSpeed);
		oldPlaneX = plr->planeX;
		plr->planeX = plr->planeX * cos(-plr->rotSpeed)
			- plr->planeY * sin(-plr->rotSpeed);
		plr->planeY = oldPlaneX * sin(-plr->rotSpeed)
			+ plr->planeY * cos(-plr->rotSpeed);
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
