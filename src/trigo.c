/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:57:50 by julthoma          #+#    #+#             */
/*   Updated: 2024/04/24 16:57:50 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	transform_point(t_vector3 point, t_camera *camera)
{
	float	cos_yaw;
	float	sin_yaw;
	float	temp;
	float	cos_pitch;
	float	sin_pitch;

	point.x -= camera->position.x;
	point.y -= camera->position.y;
	point.z -= camera->position.z;
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

t_vector2	ft_projet_vector3(t_vector3 point, t_camera *camera)
{
	point = transform_point(point, camera);
	return (project_point(point, camera));
}
