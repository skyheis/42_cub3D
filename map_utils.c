/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:00:48 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/04 17:03:01 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_substrlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0' && str[i] != 32 && str[i] != '\n')
		i++;
	return (i);
}

int	ft_isallset(t_map *map)
{
	if (!map->no_file || !map->so_file || !map->we_file || !map->ea_file)
		return (0);
	if (map->floor_color == -1 || map->cieling_color == -1)
		return (0);
	return (1);
}

static void	ft_fc_color_next(t_map *map, char *mapmem, int *i, int bits)
{
	while (ft_isdigit(mapmem[*i]))
		*i = *i + 1;
	if (mapmem[*i] == ',')
		*i = *i + 1;
	else if (bits < 0 && (mapmem[*i] == 32 || mapmem[*i] == '\n'))
	{
		while (mapmem[*i] == 32)
			*i = *i + 1;
	}
	else
		ft_exit_map(map, "Error: color wrong format\n");
}

void	ft_get_fc_color(t_map *map, char *mapmem, int *i, int *color)
{
	int	times;
	int	atoi;
	int	bits;

	if (*color != -1)
		ft_exit_map(map, "Error: color wrong format\n");
	*color = 0;
	times = 0;
	bits = 16;
	*i = *i + 1;
	while (mapmem[*i] == 32)
		*i = *i + 1;
	while (times++ < 3)
	{
		atoi = ft_atoi(&mapmem[*i]);
		if (atoi < 0 || atoi > 255)
			exit(1); //ft_exit_map
		*color |= atoi << bits;
		bits -= 8;
		ft_fc_color_next(map, mapmem, i, bits);
	}
}

void	ft_wallimage_path(t_map *map, char *mapmem, int *i, char **wallpath)
{
	int	j;
	int	fd;

	if (*wallpath)
		ft_exit_map(map, "Error: duplicate wall rule\n");
	j = 0;
	*i = *i + 2;
	while (mapmem[*i] == 32)
		*i = *i + 1;
	*wallpath = ft_calloc(ft_substrlen(&mapmem[*i]) + 1, sizeof(char));
	if (!*wallpath)
		ft_exit_map(map, "Error: malloc failed\n");
	while (mapmem[*i] != '\0' && mapmem[*i] != 32 && mapmem[*i] != '\n')
	{
		(*wallpath)[j] = mapmem[*i];
		*i = *i + 1;
		j++;
	}
	while (mapmem[*i] == ' ')
		*i = *i + 1;
	fd = open(*wallpath, O_RDONLY);
	if (fd == -1)
		ft_exit_map(map, "Error: wall's image does not exist\n");
	close(fd);
}
