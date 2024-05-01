/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:00:27 by julthoma          #+#    #+#             */
/*   Updated: 2024/04/24 20:00:27 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_right(t_map *map)
{
	map->camera->position.x += 0.5 * cos(map->camera->yaw);
	map->camera->position.z -= 0.5 * sin(map->camera->yaw);
}

void	ft_left(t_map *map)
{
	map->camera->position.x -= 0.5 * cos(map->camera->yaw);
	map->camera->position.z += 0.5 * sin(map->camera->yaw);
}

void	ft_forward(t_map *map)
{
	map->camera->position.x -= 0.5 * sin(map->camera->yaw);
	map->camera->position.z -= 0.5 * cos(map->camera->yaw);
}

void	ft_backward(t_map *map)
{
	map->camera->position.x += 0.5 * sin(map->camera->yaw);
	map->camera->position.z += 0.5 * cos(map->camera->yaw);
}
