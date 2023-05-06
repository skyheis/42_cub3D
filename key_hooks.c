/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:20:26 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/06 13:40:19 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_terminate(t_mlxvars *meta)
{
	mlx_destroy_window(meta->mlx, meta->win);
	exit(0);
}

void	ft_destroy(t_mlxvars *meta)
{
	mlx_destroy_window(meta->mlx, meta->win);
	ft_printf("quit\n");
	exit(0);
}

int	key_hooks(int keycode, t_mlxvars *meta)
{
	double		oldDirX;
	double		oldPlaneX;
	t_player	*plr;

	plr = &meta->plr;
	if (keycode == B_ESC)
		ft_destroy(meta);
	//move forward if no wall in front of you
	if(keycode == UP)
	{
		//printf("- dirX %i\n - moveSpeed %i\n", plr->dirX );
		if(meta->map.map[(int)(plr->posX + plr->dirX * plr->moveSpeed)][(int)plr->posY] == '.')
			plr->posX += plr->dirX * plr->moveSpeed;
		if(meta->map.map[(int)plr->posX][(int)(plr->posY + plr->dirY * plr->moveSpeed)] == '.')
			plr->posY += plr->dirY * plr->moveSpeed;
	}
	//move backwards if no wall behind you
	if(keycode == DOWN)
	{
		if(meta->map.map[(int)(plr->posX - plr->dirX * plr->moveSpeed)][(int)plr->posY] == '.')
			plr->posX -= plr->dirX * plr->moveSpeed;
		if(meta->map.map[(int)plr->posX][(int)(plr->posY - plr->dirY * plr->moveSpeed)] == '.')
			plr->posY -= plr->dirY * plr->moveSpeed;
	}
	//rotate to the right
	if(keycode == RIGHT)
	{
		//both camera direction and camera plane must be rotated
		oldDirX = plr->dirX;
		plr->dirX = plr->dirX * cos(-plr->rotSpeed) - plr->dirY * sin(-plr->rotSpeed);
		plr->dirY = oldDirX * sin(-plr->rotSpeed) + plr->dirY * cos(-plr->rotSpeed);
		oldPlaneX = plr->planeX;
		plr->planeX = plr->planeX * cos(-plr->rotSpeed) - plr->planeY * sin(-plr->rotSpeed);
		plr->planeY = oldPlaneX * sin(-plr->rotSpeed) + plr->planeY * cos(-plr->rotSpeed);
	}
	//rotate to the left
	if(keycode == LEFT)
	{
		//both camera direction and camera plane must be rotated
		oldDirX = plr->dirX;
		plr->dirX = plr->dirX * cos(plr->rotSpeed) - plr->dirY * sin(plr->rotSpeed);
		plr->dirY = oldDirX * sin(plr->rotSpeed) + plr->dirY * cos(plr->rotSpeed);
		oldPlaneX = plr->planeX;
		plr->planeX = plr->planeX * cos(plr->rotSpeed) - plr->planeY * sin(plr->rotSpeed);
		plr->planeY = oldPlaneX * sin(plr->rotSpeed) + plr->planeY * cos(plr->rotSpeed);
	}
	return (0);
}
