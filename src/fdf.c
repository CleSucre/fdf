/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 02:17:22 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 06:53:21 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_camera	*ft_init_camera(t_map *map)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	camera->position.x = map->size_x * 0.90;
	camera->position.y = map->size_y + (map->size_z * 0.90);
	camera->position.z = map->size_z * 0.90;
	camera->yaw = 1.0f;
	camera->pitch = 0.90f;
	camera->fov = 80.0f;
	return (camera);
}

static t_win	*ft_init_window(char *filename)
{
	t_win	*win;

	win = (t_win *)malloc(sizeof(t_win));
	if (win == NULL)
	{
		ft_printf("malloc error in ft_init_window\n");
		exit(0);
	}
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			filename);
	win->img_ptr = mlx_new_image(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	return (win);
}

static void	ft_create_image(t_win *win)
{
	int	bpp;
	int	size_line;
	int	endian;

	win->img_data = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
	win->img_size = SCREEN_WIDTH * SCREEN_HEIGHT * (bpp / 8);
	win->bpp = bpp;
	win->size_line = size_line;
}

static int	ft_fdf(char *filename)
{
	t_map	*map;
	int		fd;
	t_win	*win;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n");
		return (1);
	}
	map = ft_get_map_from_file(fd);
	close(fd);
	if (map == NULL)
		return (1);
	win = ft_init_window(filename);
	ft_init_keymap(win, map);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	ft_create_image(win);
	ft_refresh_window(win, map);
	mlx_loop(win->mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("usage: ./fdf <filename>\n");
		return (0);
	}
	return (ft_fdf(argv[1]));
}
