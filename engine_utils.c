/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:14:46 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/10 16:24:51 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_WIDTH || x <= 0 || y >= WIN_HEIGHT || y <= 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	get_tex_color(t_texture *tex, int tex_num)
{
	if (tex->texX >= 0 && tex->texX < tex->texWidth && tex->texY >= 0 && tex->texY < tex->texHeight)
	{
		return (*(int*)(tex->imgs[tex_num].addr + (4 * tex->texWidth * (int)tex->texY) + (4 * (int)tex->texX)));
	}
	return (0x0);
}

int	focus_in(void *p)
{
	t_mlxvars	*meta;

	meta = (t_mlxvars *)p;
	meta->mouse = true;
	return (0);
}

int	focus_out(void *p)
{
	t_mlxvars	*meta;

	meta = (t_mlxvars *)p;
	meta->mouse = false;
	return (0);
}
