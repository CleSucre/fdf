/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:51:50 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 02:09:27 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "key_map_bonus.h"

static int	action_key(int keycode, t_key_params *params)
{
	if (keycode == KEY_ESC)
		ft_free_program(params);
	else if (keycode == KEY_D)
		ft_right(params->map);
	else if (keycode == KEY_S)
		ft_backward(params->map);
	else if (keycode == KEY_A)
		ft_left(params->map);
	else if (keycode == KEY_W)
		ft_forward(params->map);
	else if (keycode == KEY_Q)
		params->map->camera->position.y += 0.5;
	else if (keycode == KEY_E)
		params->map->camera->position.y -= 0.5;
	else
		return (0);
	ft_refresh_window(params->win, params->map);
	return (1);
}

static int	ft_scroll(int keycode, t_key_params *params)
{
	if (keycode == 4)
	{
		params->map->camera->position.x -= sin(params->map->camera->yaw)
			* cos(params->map->camera->pitch);
		params->map->camera->position.y -= sin(params->map->camera->pitch);
		params->map->camera->position.z -= cos(params->map->camera->yaw)
			* cos(params->map->camera->pitch);
	}
	else if (keycode == 5)
	{
		params->map->camera->position.x += sin(params->map->camera->yaw)
			* cos(params->map->camera->pitch);
		params->map->camera->position.y += sin(params->map->camera->pitch);
		params->map->camera->position.z += cos(params->map->camera->yaw)
			* cos(params->map->camera->pitch);
	}
	else
		return (0);
	ft_refresh_window(params->win, params->map);
	return (1);
}

static int	action_mouse_key(int button, int x, int y, void *params)
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

static int	action_mouse_move(int x, int y, void *params)
{
	t_key_params	*key_params;

	key_params = (t_key_params *)params;
	if ((key_params->map->camera->mouse->lock))
	{
		key_params->map->camera->yaw
			+= (key_params->map->camera->mouse->last_pos.x - x) * 0.001;
		key_params->map->camera->pitch
			-= (key_params->map->camera->mouse->last_pos.y - y) * 0.001;
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

void	ft_init_keymap(t_win *win, t_map *map)
{
	t_key_params	*params;

	params = (t_key_params *)malloc(sizeof(t_key_params));
	if (params == NULL)
	{
		ft_printf("malloc error in ft_init_keymap\n");
		exit(0);
	}
	params->win = win;
	params->map = map;
	mlx_do_key_autorepeaton(win->mlx_ptr);
	mlx_mouse_hook(win->win_ptr, action_mouse_key, params);
	mlx_hook(win->win_ptr, 5, 1L << 3, action_mouse_key, params);
	mlx_hook(win->win_ptr, 2, 1L << 0, action_key, params);
	mlx_hook(win->win_ptr, 6, 1L << 6, action_mouse_move, params);
	mlx_hook(win->win_ptr, 17, 1L << 17, ft_free_program, params);
}
