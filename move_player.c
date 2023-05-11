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
		if (meta->map.map[(int)(plr->posx + plr->dirx * plr->move_speed)]
			[(int)plr->posy] == '.')
			plr->posx += plr->dirx * plr->move_speed;
		if (meta->map.map[(int)plr->posx]
			[(int)(plr->posy + plr->diry * plr->move_speed)] == '.')
			plr->posy += plr->diry * plr->move_speed;
	}
	if (keycode == S_KEY)
	{
		if (meta->map.map[(int)(plr->posx - plr->dirx * plr->move_speed)]
			[(int)plr->posy] == '.')
			plr->posx -= plr->dirx * plr->move_speed;
		if (meta->map.map[(int)plr->posx]
			[(int)(plr->posy - plr->diry * plr->move_speed)] == '.')
			plr->posy -= plr->diry * plr->move_speed;
	}
}

void	ft_move_plr_lr(int keycode, t_player *plr, t_mlxvars *meta)
{
	if (keycode == A_KEY)
	{
		if (meta->map.map[(int)(plr->posx - plr->diry * plr->move_speed)]
			[(int)plr->posy] == '.')
			plr->posx -= plr->diry * plr->move_speed;
		if (meta->map.map[(int)plr->posx]
			[(int)(plr->posy + plr->dirx * plr->move_speed)] == '.')
			plr->posy += plr->dirx * plr->move_speed;
	}
	if (keycode == D_KEY)
	{
		if (meta->map.map[(int)(plr->posx + plr->diry * plr->move_speed)]
			[(int)plr->posy] == '.')
			plr->posx += plr->diry * plr->move_speed;
		if (meta->map.map[(int)plr->posx]
			[(int)(plr->posy - plr->dirx * plr->move_speed)] == '.')
			plr->posy -= plr->dirx * plr->move_speed;
	}
}
