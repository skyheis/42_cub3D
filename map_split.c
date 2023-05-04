/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:58:03 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/04 16:58:55 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_longestline(char *str)
{
	int	i;
	int	longest;
	int	current;

	i = 0;
	longest = 0;
	current = 0;
	while (str && str[i])
	{
		current++;
		if (str[i] == '\n')
		{
			if (current > longest)
				longest = current;
			current = 0;
		}
		i++;
	}
	return (longest);
}

static int	ft_countlines(char *str)
{
	int	i;
	int bn;

	i = 0;
	bn = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			bn++;
		i++;
	}
	return (bn);
}

char	**ft_splitmap(t_map *map, char *onlymap)
{
	int	i;
	int	y;
	char	**split;

	i = 0;
	y = 0;
	split = (char **) ft_calloc(ft_countlines(onlymap) + 1, sizeof(char *));
	map->width = ft_longestline(onlymap);
	while (onlymap && onlymap[i])
	{
		split[y] = (char *) ft_calloc(map->width + 1, sizeof(char));
		ft_strlcpy(split[y], &onlymap[i], ft_findchar(&onlymap[i], '\n') + 2);
		while (onlymap[i] && onlymap[i] != '\n')
			i++;
		if (onlymap[i] == '\n')
			i++;
		y++;
	}
	map->hight = y;
	return (split);
}
