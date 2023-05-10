/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:18:52 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/10 10:02:37 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENGINE_H
# define ENGINE_H

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_player
{
	/*PLAYER DATA*/
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
}				t_player;

typedef struct	s_ray
{
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
	int dio;
	double time; //time of current frame
	double oldTime; //time of previous frame
}				t_ray;

typedef struct	s_texture
{
	t_data imgs[4];
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
	int	minimap;
	t_data	plricon[3];
	int icon8w;
	int icon8h;
	int icon16w;
	int icon16h;
	int icon32w;
	int icon32h;
	int mapf;
}				t_texture;

typedef struct	s_map
{
	char	**map;
	char	*map_memory;
	int		width;
	int		hight;
	char	*no_file;;
	char	*so_file;;
	char	*we_file;;
	char	*ea_file;;
	int		floor_color;
	int		cieling_color;
	int		player[3];
}				t_map;

#endif
