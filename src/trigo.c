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

void	transform_point(t_vector3 *dst, t_vector3 *point, t_camera *camera)
{
	float	cos_yaw;
	float	sin_yaw;
	float	temp;
	float	cos_pitch;
	float	sin_pitch;

	dst->x = point->x - camera->position.x;
	dst->y = point->y - camera->position.y;
	dst->z = point->z - camera->position.z;
	cos_yaw = cosf(camera->yaw);
	sin_yaw = sinf(camera->yaw);
	temp = dst->x * cos_yaw - dst->z * sin_yaw;
	dst->z = dst->x * sin_yaw + dst->z * cos_yaw;
	dst->x = temp;
	cos_pitch = cosf(camera->pitch);
	sin_pitch = sinf(camera->pitch);
	temp = dst->y * cos_pitch - dst->z * sin_pitch;
	dst->z = dst->y * sin_pitch + dst->z * cos_pitch;
	dst->x /= dst->z;
	dst->y = temp / dst->z;
}

static void	project_point(t_vector2 *dst, t_vector3 *point, t_camera *camera)
{
	float		screen_distance;

	screen_distance = tanf(camera->fov * 0.5f);
	dst->x = (point->x / screen_distance + 1.0f)
		* 0.5f * SCREEN_WIDTH;
	dst->y = (1.0f - point->y / screen_distance)
		* 0.5f * SCREEN_HEIGHT;
}

void	ft_projet_vector3(t_vector2 *dst, t_vector3 *point, t_camera *camera)
{
	project_point(dst, point, camera);
}

int	ft_check_frustum(t_vector3 *transformed_point)
{
    if (transformed_point->z > 0)
        return (0);
    return (1);
}