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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	move_speed;
	double	rot_speed;
}				t_player;

/* 	//calculate ray position and direction
	double camera_x;//x-coordinate in camera space
	double ray_dirx;
	double ray_diry;
	//which box of the map we're in
	int mapx;
	int mapy;
	//length of ray from current position to next x or y-side
	double side_distx;
	double side_disty;
	//length of ray from one x or y-side to next x or y-side
	double delta_distx;
	double delta_disty;
	double perp_walldist;
	//what direction to step in x or y-direction (either +1 or -1)
	int stepx;
	int step_y;
	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	int dio;
	double time; //time of current frame
	double oldtime; //time of previous frame */
typedef struct s_ray
{
	double	camera_x;
	double	ray_dirx;
	double	ray_diry;
	int		mapx;
	int		mapy;
	double	side_distx;
	double	side_disty;
	double	delta_distx;
	double	delta_disty;
	double	perp_walldist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		dio;
	double	time;
	double	oldtime;
}				t_ray;

/* 	//calculate lowest and highest pixel to fill in current stripe
	int draw_start;
	int draw_end;
	//calculate value of wallx
	double wallx; //where exactly the wall was hit
	//x coordinate on the texture
	int tex_x;
	int tex_y;
	// How much to increase the texture coordinate per screen pixel
	double step;
	// Starting texture coordinate
	double tex_pos;
	int	minimap; */
typedef struct s_texture
{
	t_data	imgs[4];
	int		tex_width;
	int		tex_height;
	int		line_height;
	int		pitch;
	int		draw_start;
	int		draw_end;
	double	wallx;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		minimap;
	t_data	plricon[3];
	int		icon8w;
	int		icon8h;
	int		icon16w;
	int		icon16h;
	int		icon32w;
	int		icon32h;
	int		mapf;
	int		picx;
	int		picy;
}				t_texture;

typedef struct s_map
{
	char	**map;
	char	*map_memory;
	int		width;
	int		hight;
	char	*no_file;
	char	*so_file;
	char	*we_file;
	char	*ea_file;
	int		floor_color;
	int		cieling_color;
	int		player[3];
}				t_map;

#endif
