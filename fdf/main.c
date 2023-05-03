/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:48:04 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/07 17:11:36 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_invalid_map(t_mlxvars *meta)
{
	free(meta);
	return (2);
}

void	ft_traspernt_img(t_data *img)
{
	int	a;
	int	b;

	b = 0;
	while (b < WIN_HEIGHT)
	{
		a = 0;
		while (a < WIN_WIDE / 6)
		{
			my_mlx_pixel_put(img, a, b, 0x202020);
			a++;
		}
		b++;
	}
}

void	ft_set_img(t_mlxvars *meta, t_data *img)
{
	if (img->img)
		mlx_destroy_image(meta->mlx, img->img);
	img->img = mlx_new_image(meta->mlx, WIN_WIDE, WIN_HEIGHT);
	meta->img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (meta->map->vision == 1)
		ft_set_dot(meta->map, ft_isometric);
	else if (meta->map->vision == 0)
		ft_set_dot(meta->map, ft_top);
	else if (meta->map->vision == 9)
		ft_set_dot(meta->map, ft_xtoz);
	else if (meta->map->vision == 8)
		ft_set_dot(meta->map, ft_ytoz);
	ft_traspernt_img(img);
	if (meta->map->vision == 2)
		ft_ortographic(meta);
	else
		ft_draw_map(meta, meta->map->map);
	mlx_put_image_to_window(meta->mlx, meta->win, meta->img->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_mlxvars	*meta;

	if (ac != 2)
		return (1);
	meta = (t_mlxvars *) malloc(sizeof(t_mlxvars));
	meta->map = ft_get_map(av);
	if (!meta->map)
		return (ft_invalid_map(meta));
	meta->img = (t_data *) malloc(sizeof(t_data));
	if (!meta->img)
		return (ft_clean_all(meta));
	meta->img->img = NULL;
	meta->mlx = mlx_init();
	if (!meta->mlx)
		return (ft_clean_all(meta));
	meta->win = mlx_new_window(meta->mlx, WIN_WIDE, WIN_HEIGHT,
			"FdF - ggiannit");
	ft_set_zoom_td(meta->map);
	ft_set_img(meta, meta->img);
	ft_menu_top(meta);
	mlx_hook(meta->win, 17, 0L, ft_if_close_x, (void *)meta);
	mlx_hook(meta->win, 2, 1L << 0, ft_key_press, (void *)meta);
	mlx_mouse_hook(meta->win, ft_mouse_press, (void *)meta);
	mlx_loop(meta->mlx);
	return (0);
}
