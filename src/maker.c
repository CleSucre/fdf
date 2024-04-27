/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:42 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 14:47:42 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_gen_horizontal_line(t_map *map, t_win *win, int i, int j)
{
	if (map->map_vector3[i][j].z >= 0 && map->map_vector3[i][j + 1].z >= 0)
	{
		ft_projet_vector3(map->point1, map->map_vector3[i][j], map->camera);
		if (ft_check_frustum(map->point1))
		{
			ft_projet_vector3(map->point2, map->map_vector3[i][j + 1],
				map->camera);
			if (ft_check_frustum(map->point1))
			{
				map->line->point1 = map->point1;
				map->line->point2 = map->point2;
				map->line->point1_color = ft_get_color_from_y(
						map->map_vector3[i][j].y, map->size_y, 0);
				map->line->point2_color = ft_get_color_from_y(
						map->map_vector3[i][j + 1].y, map->size_y, 0);
				ft_draw_line(win, map->line);
			}
		}
	}
}

static void	ft_gen_vertical_line(t_map *map, t_win *win, int i, int j)
{
	if (map->map_vector3[i][j].z >= 0 && map->map_vector3[i + 1][j].z >= 0)
	{
		ft_projet_vector3(map->point1, map->map_vector3[i][j], map->camera);
		if (ft_check_frustum(map->point1))
		{
			ft_projet_vector3(map->point2, map->map_vector3[i + 1][j],
				map->camera);
			if (ft_check_frustum(map->point2))
			{
				map->line->point1 = map->point1;
				map->line->point2 = map->point2;
				map->line->point1_color = ft_get_color_from_y(
						map->map_vector3[i][j].y, map->size_y, 0);
				map->line->point2_color = ft_get_color_from_y(
						map->map_vector3[i + 1][j].y, map->size_y, 0);
				ft_draw_line(win, map->line);
			}
		}
	}
}

void	ft_draw_map(t_map *map, t_win *win)
{
	int			i;
	int			j;

	i = 0;
	while (i < map->size_z)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (j + 1 < map->size_x)
				ft_gen_horizontal_line(map, win, i, j);
			if (i + 1 < map->size_z)
				ft_gen_vertical_line(map, win, i, j);
			j++;
		}
		i++;
	}
}

t_camera	*ft_init_camera(t_map *map)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	camera->position.x = map->size_x / 2.0f;
	camera->position.y = map->size_y / 2.0f;
	camera->position.z = map->size_z / 2.0f
		+ fmaxf(map->size_x, fmaxf(map->size_y, map->size_z));
	camera->yaw = 0;
	camera->pitch = 0;
	camera->fov = 100.0f;
	camera->mouse = (t_mouse_info *)malloc(sizeof(t_mouse_info));
	if (camera->mouse == NULL)
	{
		free(camera);
		return (NULL);
	}
	camera->mouse->lock = 0;
	camera->mouse->pos_on_lock.x = 0;
	camera->mouse->pos_on_lock.y = 0;
	return (camera);
}

void	ft_create_image(t_win *win)
{
	int	bpp;
	int	size_line;
	int	endian;

	win->img_ptr = mlx_new_image(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	win->img_data = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
	win->img_size = SCREEN_WIDTH * SCREEN_HEIGHT * (bpp / 8);
	win->bpp = bpp;
	win->size_line = size_line;
}
