/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 06:24:25 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/29 06:24:25 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Initializes a map.
 * 
 * @param size_x Size of the map on the x axis.
 * @param size_z Size of the map on the z axis.
 * @return t_map* Initialized map.
 */
static t_vector3	transform_point(t_vector3 point, t_camera *camera)
{
	float	cos_yaw;
	float	sin_yaw;
	float	temp;
	float	cos_pitch;
	float	sin_pitch;

	point = ft_make_vector3(point.x - camera->pos.x, point.y - camera->pos.y,
			point.z - camera->pos.z);
	cos_yaw = cosf(camera->yaw);
	sin_yaw = sinf(camera->yaw);
	temp = point.x * cos_yaw - point.z * sin_yaw;
	point.z = point.x * sin_yaw + point.z * cos_yaw;
	point.x = temp;
	cos_pitch = cosf(camera->pitch);
	sin_pitch = sinf(camera->pitch);
	temp = point.y * cos_pitch - point.z * sin_pitch;
	point.z = point.y * sin_pitch + point.z * cos_pitch;
	point.x /= point.z;
	point.y = temp / point.z;
	return (point);
}

/**
 * @brief Projects a 3D point to a 2D point.
 * 
 * @param point Point to project.
 * @param camera Camera information.
 * @return t_vector2 Projected point.
 */
static t_vector2	project_point(t_vector3 point, t_camera *camera)
{
	float		screen_distance;
	t_vector2	projected_point;

	screen_distance = tanf(camera->fov * 0.5f);
	projected_point.x = (point.x / screen_distance + 1.0f)
		* 0.5f * SCREEN_WIDTH;
	projected_point.y = (1.0f - point.y / screen_distance)
		* 0.5f * SCREEN_HEIGHT;
	return (projected_point);
}

/**
 * @brief Converts a 3D point to a 2D point.
 *
 * @param point Point to convert.
 * @param camera Camera information.
 * @return t_vector2 Converted point.
 */
t_vector2	ft_3d_to_2d(t_vector3 point, t_camera *camera)
{
	t_vector2	projected_point;

	point = transform_point(point, camera);
	projected_point = project_point(point, camera);
	return (projected_point);
}
