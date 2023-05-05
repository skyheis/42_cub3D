/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:08:32 by gfantech          #+#    #+#             */
/*   Updated: 2023/05/05 18:08:36 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	ft_printf("quit\n");
	exit(0);
}

int	key_hooks(int keycode, t_everything *all)
{
	if (keycode == ESC)
		destroy(&all->vars);
	//move forward if no wall in front of you
	if(keycode == UP)
	{
		if(worldMap[(int)(all->plr->posX + all->plr->dirX * all->plr->moveSpeed)][(int)all->plr->posY] == false)
			all->plr->posX += all->plr->dirX * all->plr->moveSpeed;
		if(worldMap[(int)all->plr->posX][(int)(all->plr->posY + all->plr->dirY * all->plr->moveSpeed)] == false)
			all->plr->posY += all->plr->dirY * all->plr->moveSpeed;
	}
	//move backwards if no wall behind you
	if(keycode == DOWN)
	{
		if(worldMap[(int)(all->plr->posX - all->plr->dirX * all->plr->moveSpeed)][(int)all->plr->posY] == false)
			all->plr->posX -= all->plr->dirX * all->plr->moveSpeed;
		if(worldMap[(int)all->plr->posX][(int)(all->plr->posY - all->plr->dirY * all->plr->moveSpeed)] == false)
			all->plr->posY -= all->plr->dirY * all->plr->moveSpeed;
	}
	//rotate to the right
	if(keycode == RIGHT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = all->plr->dirX;
		all->plr->dirX = all->plr->dirX * cos(-all->plr->rotSpeed) - all->plr->dirY * sin(-all->plr->rotSpeed);
		all->plr->dirY = oldDirX * sin(-all->plr->rotSpeed) + all->plr->dirY * cos(-all->plr->rotSpeed);
		double oldPlaneX = all->plr->planeX;
		all->plr->planeX = all->plr->planeX * cos(-all->plr->rotSpeed) - all->plr->planeY * sin(-all->plr->rotSpeed);
		all->plr->planeY = oldPlaneX * sin(-all->plr->rotSpeed) + all->plr->planeY * cos(-all->plr->rotSpeed);
	}
	//rotate to the left
	if(keycode == LEFT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = all->plr->dirX;
		all->plr->dirX = all->plr->dirX * cos(all->plr->rotSpeed) - all->plr->dirY * sin(all->plr->rotSpeed);
		all->plr->dirY = oldDirX * sin(all->plr->rotSpeed) + all->plr->dirY * cos(all->plr->rotSpeed);
		double oldPlaneX = all->plr->planeX;
		all->plr->planeX = all->plr->planeX * cos(all->plr->rotSpeed) - all->plr->planeY * sin(all->plr->rotSpeed);
		all->plr->planeY = oldPlaneX * sin(all->plr->rotSpeed) + all->plr->planeY * cos(all->plr->rotSpeed);
	}
	return (0);
}

int	terminate(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
