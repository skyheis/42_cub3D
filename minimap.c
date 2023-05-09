#include "cub3d.h"

static void ft_draw_base(t_mlxvars *meta, t_map map, int zoom)
{
	int x;
    int y;
	
	x = 0;
    while (x / zoom < map.hight)
    {
        y = 0;
        while (y / zoom < map.width)
        {
            if (map.map[x / zoom][y / zoom] == '1')
                my_mlx_pixel_put(&meta->main, 42 + y, 42 + x, 0xFF00FF);
            else if (map.map[x / zoom][y / zoom] == '.')
                my_mlx_pixel_put(&meta->main, 42 + y, 42 + x, 0x0);
            y++;
        }
        x++;
    }
}

int ft_draw_minimap(t_mlxvars *meta, t_map map)
{

	int zoom;

	zoom = 1;
	meta->tex.mapf = -1;
	while (map.hight * zoom < WIN_HEIGHT - 84 && map.width * zoom < WIN_WIDTH - 48)
		zoom++;
	ft_draw_base(meta, map, zoom);
	if (zoom < 10)
	{
		my_mlx_pixel_put(&meta->main, 41 + (int) (meta->plr.posY * zoom), 41 + (int) (meta->plr.posX * zoom), 0x00FF00);
		if (zoom > 3)
		{
			my_mlx_pixel_put(&meta->main, 42 + (int) (meta->plr.posY * zoom), 41 + (int) (meta->plr.posX * zoom), 0x00FF00);
			my_mlx_pixel_put(&meta->main, 41 + (int) (meta->plr.posY * zoom), 42 + (int) (meta->plr.posX * zoom), 0x00FF00);
			my_mlx_pixel_put(&meta->main, 42 + (int) (meta->plr.posY * zoom), 42 + (int) (meta->plr.posX * zoom), 0x00FF00);
		}
	}
	else if (zoom < 15)
		meta->tex.mapf = 0;
	else if (zoom < 20)
		meta->tex.mapf = 1;
	else
		meta->tex.mapf = 2;
	return (zoom);
}
