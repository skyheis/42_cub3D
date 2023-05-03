/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charinstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:34:45 by ggiannit          #+#    #+#             */
/*   Updated: 2023/05/03 11:38:01 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charinstr(char *str, char c)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_findchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
