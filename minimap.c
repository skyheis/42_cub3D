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

void ft_draw_minimap(t_mlxvars *meta, t_map map)
{

	int zoom;

	zoom = 1;
	while (map.hight * zoom < WIN_HEIGHT - 84 && map.width * zoom < WIN_WIDTH - 48)
		zoom++;
	ft_draw_base(meta, map, zoom);
	my_mlx_pixel_put(&meta->main, 41 + (int) (meta->plr.posY * 10), 41 + (int) (meta->plr.posX * 10), 0x00FF00);
	if (zoom > 3)
	{
		my_mlx_pixel_put(&meta->main, 42 + (int) (meta->plr.posY * 10), 41 + (int) (meta->plr.posX * 10), 0x00FF00);
		my_mlx_pixel_put(&meta->main, 41 + (int) (meta->plr.posY * 10), 42 + (int) (meta->plr.posX * 10), 0x00FF00);
		my_mlx_pixel_put(&meta->main, 42 + (int) (meta->plr.posY * 10), 42 + (int) (meta->plr.posX * 10), 0x00FF00);
	}
}
