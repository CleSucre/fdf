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

t_camera	*ft_init_camera(t_vector3 pos)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	camera->pos = pos;

	camera->yaw = atan2f(pos.y, pos.x) * 180 / 3.14159265;
    float distance = sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
	printf("distance %f\n", distance);
    camera->pitch = -asinf(pos.z / distance) / 3.14159265;

	camera->fov = 100.0f;
	camera->near = 0.0f;
	camera->far = 0.0f;
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

void	*ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size_z)
	{
		free(map->map_vector3[i]);
		i++;
	}
	free(map->map_vector3);
	free(map->camera);
	free(map);
	return (NULL);
}

t_map	*ft_init_map(int maxX, int maxZ)
{
	t_map	*map;
	int		i;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->map_vector3 = (t_vector3 **)malloc(sizeof(t_vector3 *) * maxZ);
	if (map->map_vector3 == NULL)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < maxZ)
	{
		map->map_vector3[i] = (t_vector3 *)malloc(sizeof(t_vector3) * maxX);
		if (map->map_vector3[i] == NULL)
			return (ft_free_map(map));
		i++;
	}
	map->size_x = maxX;
	map->size_y = 0;
	map->size_z = maxZ;
	return (map);
}
