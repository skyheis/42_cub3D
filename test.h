/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:08:12 by gfantech          #+#    #+#             */
/*   Updated: 2023/05/05 20:20:56 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "mlx.h"
#include <mlx.h>
#include "libft.h"
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>

#define screenWidth 1080
#define screenHeight 720
#define UP 65362
#define LEFT 65361
#define RIGHT 65363
#define DOWN 65364 
#define W 119
#define S 115
#define D 100
#define A 97
#define ESC 65307

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct	s_vars {
	void	*mlx;
	void	*mlx_win;
}				t_vars;

typedef struct s_player {
	/*PLAYER DATA*/
	double posX, posY;
	double dirX, dirY;
	double planeX, planeY; 
	double moveSpeed;
	double rotSpeed;
	/*RAY DATA*/
	//calculate ray position and direction
	double cameraX;//x-coordinate in camera space
	double rayDirX;
	double rayDirY;
	//which box of the map we're in
	int mapX;
	int mapY;
	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;
	//length of ray from one x or y-side to next x or y-side
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;
	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	double time; //time of current frame
	double oldTime; //time of previous frame
}	t_player;


typedef struct s_texture
{
	t_data *imgs;
	int	texWidth;
	int texHeight;
	int lineHeight;
	int pitch;
	//calculate lowest and highest pixel to fill in current stripe
	int drawStart;
	int drawEnd;
	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	//x coordinate on the texture
	int texX;
	int texY;
	// How much to increase the texture coordinate per screen pixel
	double step;
	// Starting texture coordinate
	double texPos;
}	t_texture;




typedef struct	s_everything {
	t_data	data;
	t_vars	vars;
	t_player *plr;
	t_texture *tex;
}				t_everything;


/****************/
/*    UTILS     */
/****************/

int	create_trgb(int t, int r, int g, int b);
void	destroy(t_vars *vars);
int	terminate(t_vars *vars);
int	key_hooks(int keycode, t_everything *all);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int big_draw(void * a);

#define mapWidth 24
#define mapHeight 24

extern int worldMap[mapWidth][mapHeight];

#endif
