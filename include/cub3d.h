/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:56:02 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/06 18:17:45 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "keynum.h"
# include "engine.h"
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>

//# define WIN_WIDTH  1920
//# define WIN_HEIGHT 995
# define WIN_WIDTH  1080
# define WIN_HEIGHT 720

# define READ_SIZE	100000

# define X	0
# define Y	1
# define Z	2
# define MINX 0
# define MINY 1
# define MAXX 2
# define MAXY 3

typedef struct s_mlxvars
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_data		main;
	t_player	plr;
	t_ray		ray;
	t_texture	tex;
}				t_mlxvars;

/* map map_utils map_split*/
char	**ft_splitmap(t_map *map, char *onlymap);
int		ft_substrlen(char *str);
int		ft_isallset(t_map *map);
void	ft_get_fc_color(t_map *map, char *mapmem, int *i, int *color);
void	ft_wallimage_path(t_map *map, char *mapmem, int *i, char **wallpath);
void	ft_get_map(t_map *map, char *filename);

/* check_player map */
void	ft_checkmap(t_map *map);
void	ft_findplayer(t_map *map);

/* dda */
void	ft_perform_dda(t_ray *ray, t_map *map);
void	ft_set_dda(int x, t_player *plr, t_ray *ray);

/* draw wall line */
void	ft_draw_wall_line(int x, t_mlxvars *meta, t_ray *ray, t_texture *tex);
void	ft_calc_wall_ray(t_player *plr, t_ray *ray, t_texture *tex);
void	ft_draw_cieiling_floor(t_mlxvars *meta, t_map map);

/* engine utils */
long long	get_time(void);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			get_tex_color(t_texture *tex, int tex_num);

/* key hooks */
int	ft_terminate(t_mlxvars *meta);
void	ft_destroy(t_mlxvars *meta);
int	key_hooks(int keycode, t_mlxvars *meta);

int big_draw(void * voidmeta);

/* handle error */
void	ft_exit_map(t_map *map, char *str);

/* minimap */
int ft_draw_minimap(t_mlxvars *meta, t_map map);

#endif
