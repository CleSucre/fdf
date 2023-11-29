/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:37:03 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/29 00:37:05 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Generate a map from a file
 * @param fd
 * @return t_map*
 */
t_map	*ft_get_map_from_file(int fd)
{
	t_map	*map;
	char	**lines;
	char	**positions;
	int		i;
	int		j;
	float	tz;

	lines = get_lines(fd);
	if (lines == NULL)
		return (NULL);
	i = 0;
	while (lines[i])
		i++;
	map = ft_init_map(ft_count_words(lines[0], ' '), i);
	i = 0;
	while (lines[i] && i < map->size_z)
	{
		positions = ft_split(lines[i], ' ');
		j = 0;
		while (positions[j] && j < map->size_x)
		{
			tz = ft_atoi(positions[j]) + 1;
			map->map_vector3[i][j] = ft_make_vector3(j, tz, i);
			if (tz > map->size_y)
				map->size_y = tz;
			free(positions[j]);
			j++;
		}
		free(positions);
		free(lines[i]);
		i++;
	}
	free(lines);
	map->camera = ft_init_camera(ft_make_vector3(map->size_x * 2, map->size_y
				* 3, map->size_z * 3));
	map->refresh_window = ft_refresh_window;
	return (map);
}

/**
 * @brief Converts a 3D point to a 2D point.
 *
 * @param point Point to convert.
 * @param camera Camera information.
 * @return t_vector2 Converted point.
 */
static t_vector2	ft_3d_to_2d(t_vector3 point, t_camera *camera)
{
	float		cos_yaw;
	float		sin_yaw;
	float		cos_pitch;
	float		sin_pitch;
	float		new_x;
	float		new_z;
	float		newY;
	float		new_z2;
	float		distance;
	float		screen_distance;
	t_vector2	projected_point;

	point.x -= camera->pos.x;
	point.y -= camera->pos.y;
	point.z -= camera->pos.z;
	cos_yaw = cosf(camera->yaw);
	sin_yaw = sinf(camera->yaw);
	cos_pitch = cosf(camera->pitch);
	sin_pitch = sinf(camera->pitch);
	new_x = point.x * cos_yaw - point.z * sin_yaw;
	new_z = point.x * sin_yaw + point.z * cos_yaw;
	point.x = new_x;
	point.z = new_z;
	newY = point.y * cos_pitch - point.z * sin_pitch;
	new_z2 = point.y * sin_pitch + point.z * cos_pitch;
	point.y = newY;
	point.z = new_z2;
	distance = point.z;
	point.x /= distance;
	point.y /= distance;
	screen_distance = tanf(camera->fov * 0.5f);
	point.x /= screen_distance;
	point.y /= screen_distance;
	projected_point.x = (point.x + 1.0f) * 0.5f * SCREEN_WIDTH;
	projected_point.y = (1.0f - point.y) * 0.5f * SCREEN_HEIGHT;
	return (projected_point);
}

/**
 * @brief Draws a line between two points in a 2D window.
 *
 * @param map Environment information.
 * @param camera Camera information.
 */
void	ft_draw_2d_map(t_map *map, t_camera *camera, t_win *win)
{
	int			i;
	int			j;
	t_vector2	*point1;
	t_vector2	*point2;

	point1 = (t_vector2 *)malloc(sizeof(t_vector2));
	if (point1 == NULL)
		return ;
	point2 = (t_vector2 *)malloc(sizeof(t_vector2));
	if (point2 == NULL)
	{
		free(point1);
		return ;
	}
	i = 0;
	while (i < map->size_z)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (j + 1 < map->size_x)
			{
				*point1 = ft_3d_to_2d(map->map_vector3[i][j], camera);
				*point2 = ft_3d_to_2d(map->map_vector3[i][j + 1], camera);
				ft_draw_line(win, ft_make_line(*point1, *point2,
						ft_get_color_from_y(map->map_vector3[i][j].y,
							map->size_y, 0),
						ft_get_color_from_y(map->map_vector3[i][j + 1].y,
							map->size_y, 0)));
			}
			if (i + 1 < map->size_z)
			{
				*point1 = ft_3d_to_2d(map->map_vector3[i][j], camera);
				*point2 = ft_3d_to_2d(map->map_vector3[i + 1][j], camera);
				ft_draw_line(win, ft_make_line(*point1, *point2,
						ft_get_color_from_y(map->map_vector3[i][j].y,
							map->size_y, 0),
						ft_get_color_from_y(map->map_vector3[i + 1][j].y,
							map->size_y, 0)));
			}
			j++;
		}
		i++;
	}
	free(point1);
	free(point2);
}
