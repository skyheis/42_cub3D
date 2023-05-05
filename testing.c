/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:56:21 by gfantech          #+#    #+#             */
/*   Updated: 2023/05/05 18:08:42 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
int worldMap[mapWidth][mapHeight]=
{
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void init_player(t_player *p)
{
	p->posX = 22.0;
	p->posY = 11.5;  //x and y start position
	p->dirX = -1.0;
	p->dirY = 0.0; //initial direction vector
	p->planeX = 0.0;
	p->planeY = 0.66;
	p->moveSpeed = 1; //the constant value is in squares/second
	p->rotSpeed = 0.1; //the constant value is in radians/second
}

void init_texture(t_texture *t, t_vars vars)
{
	t->imgs = malloc(sizeof(t_data) * 8);
	t->imgs[0].img = mlx_xpm_file_to_image(vars.mlx, "pics/eagle.xpm", &t->texWidth, &t->texHeight);
	t->imgs[0].addr = mlx_get_data_addr(t->imgs[0].img, &t->imgs[0].bits_per_pixel, &t->imgs[0].line_length, &t->imgs[0].endian);
	t->imgs[1].img = mlx_xpm_file_to_image(vars.mlx, "pics/redbrick.xpm", &t->texWidth, &t->texHeight);
	t->imgs[1].addr = mlx_get_data_addr(t->imgs[1].img, &t->imgs[1].bits_per_pixel, &t->imgs[1].line_length, &t->imgs[1].endian);
	t->imgs[2].img = mlx_xpm_file_to_image(vars.mlx, "pics/purplestone.xpm", &t->texWidth, &t->texHeight);
	t->imgs[2].addr = mlx_get_data_addr(t->imgs[2].img, &t->imgs[2].bits_per_pixel, &t->imgs[2].line_length, &t->imgs[2].endian);
	t->imgs[3].img = mlx_xpm_file_to_image(vars.mlx, "pics/greystone.xpm", &t->texWidth, &t->texHeight);
	t->imgs[3].addr = mlx_get_data_addr(t->imgs[3].img, &t->imgs[3].bits_per_pixel, &t->imgs[3].line_length, &t->imgs[3].endian);
	t->imgs[4].img = mlx_xpm_file_to_image(vars.mlx, "pics/bluestone.xpm", &t->texWidth, &t->texHeight);
	t->imgs[4].addr = mlx_get_data_addr(t->imgs[4].img, &t->imgs[4].bits_per_pixel, &t->imgs[4].line_length, &t->imgs[4].endian);
	t->imgs[5].img = mlx_xpm_file_to_image(vars.mlx, "pics/mossy.xpm", &t->texWidth, &t->texHeight);
	t->imgs[5].addr = mlx_get_data_addr(t->imgs[5].img, &t->imgs[5].bits_per_pixel, &t->imgs[5].line_length, &t->imgs[5].endian);
	t->imgs[6].img = mlx_xpm_file_to_image(vars.mlx, "pics/wood.xpm", &t->texWidth, &t->texHeight);
	t->imgs[6].addr = mlx_get_data_addr(t->imgs[6].img, &t->imgs[6].bits_per_pixel, &t->imgs[6].line_length, &t->imgs[6].endian);
	t->imgs[7].img = mlx_xpm_file_to_image(vars.mlx, "pics/colorstone.xpm", &t->texWidth, &t->texHeight);
	t->imgs[7].addr = mlx_get_data_addr(t->imgs[7].img, &t->imgs[7].bits_per_pixel, &t->imgs[7].line_length, &t->imgs[7].endian);
}


int get_tex_color(t_texture *tex, int texNum)
{
	if (tex->texX >= 0 && tex->texX < tex->texWidth && tex->texY >= 0 && tex->texY < tex->texHeight)
	{
		return (*(int*)(tex->imgs[texNum].addr + (4 * tex->texWidth * (int)tex->texY) + (4 * (int)tex->texX)));
	}
	return (0x0);
}

int big_draw(void * a)
{
	t_everything *all;

	all = (t_everything *)a;

	mlx_destroy_image(all->vars.mlx , all->data.img);
	all->data.img = mlx_new_image(all->vars.mlx, screenWidth, screenHeight);
	all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bits_per_pixel, &all->data.line_length, &all->data.endian);
	for(int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		all->plr->cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		all->plr->rayDirX = all->plr->dirX + all->plr->planeX*all->plr->cameraX;
		all->plr->rayDirY = all->plr->dirY + all->plr->planeY*all->plr->cameraX;
		//which box of the map we're in
		all->plr->mapX = (int)all->plr->posX;
		all->plr->mapY = (int)all->plr->posY;
		//length of ray from one x or y-side to next x or y-side
		all->plr->deltaDistX = (all->plr->rayDirX == 0) ? 1e30 : fabs(1 / all->plr->rayDirX);
		all->plr->deltaDistY = (all->plr->rayDirY == 0) ? 1e30 : fabs(1 / all->plr->rayDirY);
		all->plr->hit = 0; //was there a wall hit?
		//calculate step and initial sideDist
		if(all->plr->rayDirX < 0)
		{
			all->plr->stepX = -1;
			all->plr->sideDistX = (all->plr->posX - all->plr->mapX) * all->plr->deltaDistX;
		}
		else
		{
			all->plr->stepX = 1;
			all->plr->sideDistX = (all->plr->mapX + 1.0 - all->plr->posX) * all->plr->deltaDistX;
		}
		if(all->plr->rayDirY < 0)
		{
			all->plr->stepY = -1;
			all->plr->sideDistY = (all->plr->posY - all->plr->mapY) * all->plr->deltaDistY;
		}
		else
		{
			all->plr->stepY = 1;
			all->plr->sideDistY = (all->plr->mapY + 1.0 - all->plr->posY) * all->plr->deltaDistY;
		}
		//perform DDA
		while (all->plr->hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(all->plr->sideDistX < all->plr->sideDistY)
			{
				all->plr->sideDistX += all->plr->deltaDistX;
				all->plr->mapX += all->plr->stepX;
				all->plr->side = 0;
			}
			else
			{
				all->plr->sideDistY += all->plr->deltaDistY;
				all->plr->mapY += all->plr->stepY;
				all->plr->side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[all->plr->mapX][all->plr->mapY] > 0)
				all->plr->hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if(all->plr->side == 0)
			all->plr->perpWallDist = (all->plr->sideDistX - all->plr->deltaDistX);
		else
			all->plr->perpWallDist = (all->plr->sideDistY - all->plr->deltaDistY);
		//Calculate height of line to draw on screen
		all->tex->lineHeight = (int)(screenHeight / all->plr->perpWallDist);
		all->tex->pitch = 100;
		//calculate lowest and highest pixel to fill in current stripe
		all->tex->drawStart = -all->tex->lineHeight / 2 + screenHeight / 2 + all->tex->pitch;
		if(all->tex->drawStart < 0)
			all->tex->drawStart = 0;
		all->tex->drawEnd = all->tex->lineHeight / 2 + screenHeight / 2 + all->tex->pitch;
		if(all->tex->drawEnd >= screenHeight)
			all->tex->drawEnd = screenHeight - 1;
		//calculate value of wallX
		if(all->plr->side == 0)
			all->tex->wallX = all->plr->posY + all->plr->perpWallDist * all->plr->rayDirY;
		else
			all->tex->wallX = all->plr->posX + all->plr->perpWallDist * all->plr->rayDirX;
		all->tex->wallX -= floor((all->tex->wallX));
		//x coordinate on the texture
		all->tex->texX = (int)(all->tex->wallX * (double)all->tex->texWidth);
		if(all->plr->side == 0 && all->plr->rayDirX > 0) all->tex->texX = all->tex->texWidth - all->tex->texX - 1;
		if(all->plr->side == 1 && all->plr->rayDirY < 0) all->tex->texX = all->tex->texWidth - all->tex->texX - 1;
		// How much to increase the texture coordinate per screen pixel
		all->tex->step = 1.0 * all->tex->texHeight / all->tex->lineHeight;
		// Starting texture coordinate
		all->tex->texPos = (all->tex->drawStart - all->tex->pitch - screenHeight / 2 + all->tex->lineHeight / 2) * all->tex->step;
		int texNum = worldMap[all->plr->mapX][all->plr->mapY] - 1;
		for(int y = all->tex->drawStart; y < all->tex->drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			all->tex->texY = (int)all->tex->texPos & (all->tex->texHeight - 1);
			all->tex->texPos += all->tex->step;
			int color = get_tex_color(all->tex, texNum);
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(all->plr->side == 1)
				color = (color >> 1) & 8355711;
		 	my_mlx_pixel_put(&all->data, x,y, color);
		}
	}
	//timing for input and FPS counter
	all->plr->oldTime = all->plr->time;
	all->plr->time = get_time();
	double frameTime = (all->plr->time - all->plr->oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
	//speed modifiers
	all->plr->moveSpeed = frameTime * 10.0; //the constant value is in squares/second
	all->plr->rotSpeed = frameTime * 6.0; //the constant value is in radians/second
	mlx_put_image_to_window(all->vars.mlx, all->vars.mlx_win, all->data.img, 0,0);
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;
	t_color	rgb;
	t_everything	all;
	t_player player;
	t_texture tex;

	rgb.red = 255;
	rgb.blue = 0;
	rgb.green = 0;
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Hello world!");
	img.img = mlx_new_image(vars.mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	all.data = img;
	all.color = rgb;
	all.vars = vars;
	all.plr = &player;
	all.tex = &tex;
	
	init_player(&player);
	init_texture(&tex, vars);
	mlx_loop_hook(vars.mlx, big_draw, (void *)&all);
	mlx_hook(vars.mlx_win, 2, 1L<<0, key_hooks, &all);
	mlx_hook(vars.mlx_win, 17, 0L, terminate, &vars);
	mlx_loop(vars.mlx);
	return(0);
}
