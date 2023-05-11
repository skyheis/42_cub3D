/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:20:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/11 15:36:10 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_plr_fb(int keycode, t_player *plr, t_mlxvars *meta)
{
	if (keycode == W_KEY)
	{
		if (meta->map.map[(int)(plr->posX + plr->dirX * plr->moveSpeed)]
			[(int)plr->posY] == '.')
			plr->posX += plr->dirX * plr->moveSpeed;
		if (meta->map.map[(int)plr->posX]
			[(int)(plr->posY + plr->dirY * plr->moveSpeed)] == '.')
			plr->posY += plr->dirY * plr->moveSpeed;
	}
	if (keycode == S_KEY)
	{
		if (meta->map.map[(int)(plr->posX - plr->dirX * plr->moveSpeed)]
			[(int)plr->posY] == '.')
			plr->posX -= plr->dirX * plr->moveSpeed;
		if (meta->map.map[(int)plr->posX]
			[(int)(plr->posY - plr->dirY * plr->moveSpeed)] == '.')
			plr->posY -= plr->dirY * plr->moveSpeed;
	}
}

void	ft_move_plr_lr(int keycode, t_player *plr, t_mlxvars *meta)
{
	if (keycode == A_KEY)
	{
		if (meta->map.map[(int)(plr->posX - plr->dirY * plr->moveSpeed)]
			[(int)plr->posY] == '.')
			plr->posX -= plr->dirY * plr->moveSpeed;
		if (meta->map.map[(int)plr->posX]
			[(int)(plr->posY + plr->dirX * plr->moveSpeed)] == '.')
			plr->posY += plr->dirX * plr->moveSpeed;
	}
	if (keycode == D_KEY)
	{
		if (meta->map.map[(int)(plr->posX + plr->dirY * plr->moveSpeed)]
			[(int)plr->posY] == '.')
			plr->posX += plr->dirY * plr->moveSpeed;
		if (meta->map.map[(int)plr->posX]
			[(int)(plr->posY - plr->dirX * plr->moveSpeed)] == '.')
			plr->posY -= plr->dirX * plr->moveSpeed;
	}
}
