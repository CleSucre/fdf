/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maker_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:42 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 02:09:31 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

	win->img_data = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
	win->img_size = SCREEN_WIDTH * SCREEN_HEIGHT * (bpp / 8);
	win->bpp = bpp;
	win->size_line = size_line;
	win->gen_count = 0;
	win->last_refresh = 1;
}
