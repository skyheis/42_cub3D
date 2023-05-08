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
	if (meta->main.img)
		mlx_destroy_image(meta->mlx, meta->main.img);
	if (meta->tex.imgs[0].img)
		mlx_destroy_image(meta->mlx, meta->tex.imgs[0].img);
	if (meta->tex.imgs[0].img)
		mlx_destroy_image(meta->mlx, meta->tex.imgs[1].img);
	if (meta->tex.imgs[0].img)
		mlx_destroy_image(meta->mlx, meta->tex.imgs[2].img);
	if (meta->tex.imgs[0].img)
		mlx_destroy_image(meta->mlx, meta->tex.imgs[3].img);
	if (meta->win)
		mlx_destroy_window(meta->mlx, meta->win);
	if (meta->mlx)
		mlx_destroy_display(meta->mlx);
	ft_free_null((char **) &meta->mlx);
	ft_exit_map(&meta->map, NULL);
	exit(0);
}

void	ft_destroy(t_mlxvars *meta)
{
	mlx_destroy_window(meta->mlx, meta->win);
	ft_exit_map(&meta->map, NULL);
	exit(0);
}

void	ft_move_plr_fb(int keycode, t_player *plr, t_mlxvars *meta)
{
	if(keycode == W_KEY)
	{
		if(meta->map.map[(int)(plr->posX + plr->dirX * plr->moveSpeed)][(int)plr->posY] == '.')
			plr->posX += plr->dirX * plr->moveSpeed;
		if(meta->map.map[(int)plr->posX][(int)(plr->posY + plr->dirY * plr->moveSpeed)] == '.')
			plr->posY += plr->dirY * plr->moveSpeed;
	}
	if(keycode == S_KEY)
	{
		if(meta->map.map[(int)(plr->posX - plr->dirX * plr->moveSpeed)][(int)plr->posY] == '.')
			plr->posX -= plr->dirX * plr->moveSpeed;
		if(meta->map.map[(int)plr->posX][(int)(plr->posY - plr->dirY * plr->moveSpeed)] == '.')
			plr->posY -= plr->dirY * plr->moveSpeed;
	}
}

void	ft_move_plr_lr(int keycode, t_player *plr, t_mlxvars *meta)
{
	if(keycode == A_KEY)
	{
		if(meta->map.map[(int)(plr->posX - plr->dirY * plr->moveSpeed)][(int)plr->posY] == '.')
			plr->posX -= plr->dirY * plr->moveSpeed;
		if(meta->map.map[(int)plr->posX][(int)(plr->posY + plr->dirX * plr->moveSpeed)] == '.')
			plr->posY += plr->dirX * plr->moveSpeed;
	}
	if(keycode == D_KEY)
	{
		if(meta->map.map[(int)(plr->posX + plr->dirY * plr->moveSpeed)][(int)plr->posY] == '.')
			plr->posX += plr->dirY * plr->moveSpeed;
		if(meta->map.map[(int)plr->posX][(int)(plr->posY - plr->dirX * plr->moveSpeed)] == '.')
			plr->posY -= plr->dirX * plr->moveSpeed;
	}
}

void	ft_rotate_cam(int keycode, t_player *plr)
{
	double		oldDirX;
	double		oldPlaneX;

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
}


int	key_hooks(int keycode, t_mlxvars *meta)
{
	t_player	*plr;

	plr = &meta->plr;
	if (keycode == B_ESC)
		ft_terminate(meta);
	ft_move_plr_fb(keycode, plr, meta);
	ft_move_plr_lr(keycode, plr, meta);
	ft_rotate_cam(keycode, plr);
	return (0);
}
