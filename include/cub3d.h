/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:56:02 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/05 10:33:53 by ggiannit         ###   ########.fr       */
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

/* map map_utils map_split*/
char	**ft_splitmap(t_map *map, char *onlymap);
int		ft_substrlen(char *str);
int		ft_isallset(t_map *map);
void	ft_get_fc_color(char *mapmem, int *i, int *color);
void	ft_wallimage_path(char *mapmem, int *i, char **wallpath);
void	ft_get_map(t_map *map, char *filename);

/* check_player map */
void	ft_checkmap(t_map *map);
void	ft_findplayer(t_map *map);

#endif
