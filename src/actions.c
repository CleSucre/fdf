/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 07:26:35 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 07:26:35 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "key_map.h"

static int	ft_movement_key(int keycode, t_key_params *params)
{
	if (keycode == KEY_D)
	{
		params->map->camera->pos.x += 0.5 * cos(params->map->camera->yaw);
		params->map->camera->pos.z -= 0.5 * sin(params->map->camera->yaw);
	}
	else if (keycode == KEY_S)
	{
		params->map->camera->pos.x += 0.5 * sin(params->map->camera->yaw);
		params->map->camera->pos.z += 0.5 * cos(params->map->camera->yaw);
	}
	else if (keycode == KEY_Q)
	{
		params->map->camera->pos.x -= 0.5 * cos(params->map->camera->yaw);
		params->map->camera->pos.z += 0.5 * sin(params->map->camera->yaw);
	}
	else if (keycode == KEY_Z)
	{
		params->map->camera->pos.x -= 0.5 * sin(params->map->camera->yaw);
		params->map->camera->pos.z -= 0.5 * cos(params->map->camera->yaw);
	}
	else
		return (0);
	params->map->refresh_window(params->win, params->map);
	return (1);
}

int	action_key(int keycode, t_key_params *params)
{
	if (keycode == KEY_ESC)
		ft_free_program(params);
	else if (ft_movement_key(keycode, params))
		return (0);
	else if (keycode == KEY_A)
		params->map->camera->pos.y += 1;
	else if (keycode == KEY_E)
		params->map->camera->pos.y -= 1;
	else if (keycode == KEY_RIGHT)
		params->map->camera->yaw -= M_PI / 180.0f;
	else if (keycode == KEY_LEFT)
		params->map->camera->yaw += M_PI / 180.0f;
	else if (keycode == KEY_UP)
		params->map->camera->pitch -= M_PI / 180.0f;
	else if (keycode == KEY_DOWN)
		params->map->camera->pitch += M_PI / 180.0f;
	else
		return (0);
	return (0);
}

static int	ft_scroll(int keycode, t_key_params *params)
{
	if (keycode == 4)
	{
		params->map->camera->pos.x -= sin(params->map->camera->yaw)
			* cos(params->map->camera->pitch);
		params->map->camera->pos.y -= sin(params->map->camera->pitch);
		params->map->camera->pos.z -= cos(params->map->camera->yaw)
			* cos(params->map->camera->pitch);
	}
	else if (keycode == 5)
	{
		params->map->camera->pos.x += sin(params->map->camera->yaw)
			* cos(params->map->camera->pitch);
		params->map->camera->pos.y += sin(params->map->camera->pitch);
		params->map->camera->pos.z += cos(params->map->camera->yaw)
			* cos(params->map->camera->pitch);
	}
	else
		return (0);
	params->map->refresh_window(params->win, params->map);
	return (1);
}

int	action_mouse_key(int button, int x, int y, void *params)
{
	t_key_params	*key_params;
	t_camera		*camera;

	camera = ((t_key_params *)params)->map->camera;
	key_params = (t_key_params *)params;
	if (button == 1)
	{
		if (camera->mouse->lock)
		{
			mlx_mouse_move(key_params->win->mlx_ptr, key_params->win->win_ptr,
				camera->mouse->pos_on_lock.x, camera->mouse->pos_on_lock.y);
			mlx_mouse_show(key_params->win->mlx_ptr, key_params->win->win_ptr);
		}
		else
		{
			camera->mouse->pos_on_lock.x = x;
			camera->mouse->pos_on_lock.y = y;
			mlx_mouse_hide(key_params->win->mlx_ptr, key_params->win->win_ptr);
		}
		camera->mouse->lock = !camera->mouse->lock;
	}
	else if (ft_scroll(button, key_params))
		return (1);
	ft_refresh_window(key_params->win, key_params->map);
	return (0);
}

int	action_mouse_move(int x, int y, void *params)
{
	t_key_params	*key_params;

	key_params = (t_key_params *)params;
	if ((key_params->map->camera->mouse->lock))
	{
		key_params->map->camera->yaw
			+= (key_params->map->camera->mouse->last_pos.x - x) * 0.001f;
		key_params->map->camera->pitch
			-= (key_params->map->camera->mouse->last_pos.y - y) * 0.001f;
		if (x < 0)
			mlx_mouse_move(key_params->win->mlx_ptr, key_params->win->win_ptr,
				0, y);
		else if (x > SCREEN_WIDTH)
			mlx_mouse_move(key_params->win->mlx_ptr, key_params->win->win_ptr,
				SCREEN_WIDTH, y);
		ft_refresh_window(key_params->win, key_params->map);
	}
	key_params->map->camera->mouse->last_pos.x = x;
	key_params->map->camera->mouse->last_pos.y = y;
	return (0);
}
