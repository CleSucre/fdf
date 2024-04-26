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

t_vector3	ft_make_vector3(float x, float y, float z)
{
	t_vector3	vector3;

	vector3.x = x;
	vector3.y = y;
	vector3.z = z;
	return (vector3);
}

t_vector2	ft_make_vector2(float x, float y)
{
	t_vector2	vector2;

	vector2.x = x;
	vector2.y = y;
	return (vector2);
}

t_line	ft_make_line(t_vector2 point1, t_vector2 point2, int point1_color,
		int point2_color)
{
	t_line	line;

	line.point1 = point1;
	line.point2 = point2;
	line.point1_color = point1_color;
	line.point2_color = point2_color;
	return (line);
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
