/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 07:26:35 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 07:26:35 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "key_map.h"

void    ft_rotate_camera_to_right(t_camera *camera, float degrees)
{
    camera->yaw -= degrees * (M_PI / 180.0f);
}

void    ft_rotate_camera_to_left(t_camera *camera, float degrees)
{
    camera->yaw += degrees * (M_PI / 180.0f);
}

void    ft_rotate_camera_up(t_camera *camera, float degrees)
{
    camera->pitch -= degrees * (M_PI / 180.0f);
}

void    ft_rotate_camera_down(t_camera *camera, float degrees)
{
    camera->pitch += degrees * (M_PI / 180.0f);
}

void    ft_move_camera_forward(t_camera *camera, float distance)
{
    camera->pos.x -= distance * sin(camera->yaw);
    camera->pos.z -= distance * cos(camera->yaw);
}

void    ft_move_camera_backward(t_camera *camera, float distance)
{
    camera->pos.x += distance * sin(camera->yaw);
    camera->pos.z += distance * cos(camera->yaw);
}

void    ft_move_camera_right(t_camera *camera, float distance)
{
    camera->pos.x += distance * cos(camera->yaw);
    camera->pos.z -= distance * sin(camera->yaw);
}

void    ft_move_camera_left(t_camera *camera, float distance)
{
    camera->pos.x -= distance * cos(camera->yaw);
    camera->pos.z += distance * sin(camera->yaw);
}

int action_window(int keycode, t_key_params *params)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(params->win->mlx_ptr, params->win->win_ptr);
        exit(0);
    } else if (keycode == KEY_D)
    {
        ft_move_camera_right(&params->map->camera, 1);
    }
    else if (keycode == KEY_S)
    {
        ft_move_camera_backward(&params->map->camera, 1);
    }
    else if (keycode == KEY_Q)
    {
        ft_move_camera_left(&params->map->camera, 1);
    }
    else if (keycode == KEY_Z)
    {
        ft_move_camera_forward(&params->map->camera, 1);
    }
    else if (keycode == KEY_A)
    {
        params->map->camera.pos.y += 1;
    }
    else if (keycode == KEY_E)
    {
        params->map->camera.pos.y -= 1;
    }
    else if (keycode == KEY_RIGHT)
    {
        ft_rotate_camera_to_right(&params->map->camera, 1);
    }
    else if (keycode == KEY_LEFT)
    {
        ft_rotate_camera_to_left(&params->map->camera, 1);
    }
    else if (keycode == KEY_UP)
    {
        ft_rotate_camera_up(&params->map->camera, 1);
    }
    else if (keycode == KEY_DOWN)
    {
        ft_rotate_camera_down(&params->map->camera, 1);
    }
    else
        return (0);
    params->map->refresh_window(params->win, params->map);
    return (0);
}
