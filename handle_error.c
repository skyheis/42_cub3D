#include "cub3d.h"

void	ft_exit_map(t_map *map, char *str)
{
	ft_free_null(&map->no_file);
	ft_free_null(&map->so_file);
	ft_free_null(&map->we_file);
	ft_free_null(&map->ea_file);
	ft_free_null(&map->map_memory);
	ft_free_matrix(&map->map);
	ft_putstr_fd(str, 2);
	exit(1);
}
