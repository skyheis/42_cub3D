/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:56:02 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/03 10:56:39 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "libftprintf.h"
# include "mlx.h"
# include "keynum.h"
# include <math.h>

# define WIN_WIDE 1920
# define WIN_HEIGHT 995

# define READ_SIZE	100000

# define X	0
# define Y	1
# define Z	2
# define MINX 0
# define MINY 1
# define MAXX 2
# define MAXY 3

typedef struct s_dot
{
	float	x;
	float	y;
	int		z;
	int		col;
}				t_dot;

typedef struct s_map
{
	char			*map_memory;
	t_dot			**map;
	int				x;
	int				y;
	int				check_x;
	int				zoom;
	double			angle;
	int				alpha;
	int				beta;
	int				gamma;
	unsigned char	vision;
	int				zx;
	int				zy;
	int				min_x;
	int				min_y;
	int				max_x;
	int				max_y;
	int				*minmax;
}				t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlxvars
{
	void	*mlx;
	void	*win;
	t_data	*img;
	t_map	*map;
}				t_mlxvars;

/* main */
void	ft_set_img(t_mlxvars *meta, t_data *img);

/* map and utils */
t_map	*ft_get_map(char **av);
int		ft_check_n_size_map(t_map *map);
int		ft_popol_map(t_map *map);

/* set dot */
int		ft_set_dot(t_map *map, void (*ft_vision)(t_dot *, t_map *));
void	ft_set_orto(t_map *map, int new_zx, int new_zy,
			void (*ft_vision)(t_dot *, t_map *));
int		ft_reset_minmax(t_map *map);
void	ft_fill_minmax(t_map *map, int the_x, int the_y);

/* zoomfix */
void	ft_set_zoom_td(t_map *map);
void	ft_orto_zoomfix(t_map *map);
int		check_zoomfit_down(t_map *map, int new_zx, int new_zy, int k);

/* geometry */
void	ft_top(t_dot *dot, t_map *map);
void	ft_ytoz(t_dot *dot, t_map *map);
void	ft_xtoz(t_dot *dot, t_map *map);
void	ft_isometric(t_dot *dot, t_map *map);
void	ft_rotate_z(t_dot *dot, t_map *map);

/* key hooker */
int		ft_if_close_x(t_mlxvars *meta);
int		ft_key_press(int key_code, t_mlxvars *meta);
int		ft_mouse_press(int key_code, int x, int y, t_mlxvars *meta);

/* draw_map */
void	ft_bresenham(t_mlxvars *meta, t_dot one, t_dot two);
void	ft_draw_map(t_mlxvars *meta, t_dot **map);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* ortograpihc */
void	ft_ortographic(t_mlxvars *meta);
void	ft_greyline_top(t_mlxvars *meta);
void	ft_greyline_down(t_mlxvars *meta);
void	ft_greyline_right(t_mlxvars *meta);
t_dot	ft_orto_minxdot(t_map *map);
t_dot	ft_orto_minydot(t_map *map);

/* clean close */
int		ft_free_map(t_map *map);
int		ft_clean_all(t_mlxvars *meta);

/* menu */
void	ft_menu_top(t_mlxvars *meta);

#endif
