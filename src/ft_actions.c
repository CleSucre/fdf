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

void    ft_move_zoom_in(t_camera *camera, float distance)
{
    camera->pos.x -= distance * sin(camera->yaw) * cos(camera->pitch);
    camera->pos.y -= distance * sin(camera->pitch);
    camera->pos.z -= distance * cos(camera->yaw) * cos(camera->pitch);
}

void    ft_move_zoom_out(t_camera *camera, float distance)
{
    camera->pos.x += distance * sin(camera->yaw) * cos(camera->pitch);
    camera->pos.y += distance * sin(camera->pitch);
    camera->pos.z += distance * cos(camera->yaw) * cos(camera->pitch);
}

int action_key(int keycode, t_key_params *params)
{
    ft_printf("keycode: %d\n", keycode);
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(params->win->mlx_ptr, params->win->win_ptr);
        ft_free_program(params);
        free(params);
        exit(0);
    } else if (keycode == KEY_D)
    {
        ft_move_camera_right(params->map->camera, 0.5);
    }
    else if (keycode == KEY_S)
    {
        ft_move_camera_backward(params->map->camera, 0.5);
    }
    else if (keycode == KEY_Q)
    {
        ft_move_camera_left(params->map->camera, 0.5);
    }
    else if (keycode == KEY_Z)
    {
        ft_move_camera_forward(params->map->camera, 0.5);
    }
    else if (keycode == KEY_A)
    {
        params->map->camera->pos.y += 1;
    }
    else if (keycode == KEY_E)
    {
        params->map->camera->pos.y -= 1;
    }
    else if (keycode == KEY_RIGHT)
    {
        ft_rotate_camera_to_right(params->map->camera, 1);
    }
    else if (keycode == KEY_LEFT)
    {
        ft_rotate_camera_to_left(params->map->camera, 1);
    }
    else if (keycode == KEY_UP)
    {
        ft_rotate_camera_up(params->map->camera, 1);
    }
    else if (keycode == KEY_DOWN)
    {
        ft_rotate_camera_down(params->map->camera, 1);
    }
    else
        return (0);
    //ft_printf("yaw: %f, pitch: %f\n", params->map->camera->yaw, params->map->camera->pitch);
    params->map->refresh_window(params->win, params->map);
    return (0);
}

int action_mouse_key(int button, int x, int y, void *params)
{
    t_key_params *key_params;

    key_params = (t_key_params *)params;
    ft_printf("mouse button: %d, x: %d, y: %d\n", button, x, y);
    if (button == 1)
    {
        if (key_params->map->camera->mouse->lock)
        {
            mlx_mouse_move(key_params->win->mlx_ptr, key_params->win->win_ptr, key_params->map->camera->mouse->pos_on_lock.x, key_params->map->camera->mouse->pos_on_lock.y);
            mlx_mouse_show(key_params->win->mlx_ptr, key_params->win->win_ptr);
        }
        else
        {
            key_params->map->camera->mouse->pos_on_lock.x = x;
            key_params->map->camera->mouse->pos_on_lock.y = y;
            mlx_mouse_hide(key_params->win->mlx_ptr, key_params->win->win_ptr);
        }
        key_params->map->camera->mouse->lock = !key_params->map->camera->mouse->lock;
    }
    else if (button == 4)
        ft_move_zoom_in(key_params->map->camera, 1);
    else if (button == 5)
        ft_move_zoom_out(key_params->map->camera, 1);
    ft_refresh_window(key_params->win, key_params->map);
    return (0);
}

int action_mouse_move(int x, int y, void *params)
{
    t_key_params *key_params;

    key_params = (t_key_params *)params;
    ft_printf("mouse position: x: %d, y: %d\n", x, y);
    if ((key_params->map->camera->mouse->lock))
    {
        //rotate the all map
        key_params->map->camera->yaw += (key_params->map->camera->mouse->last_pos.x - x) * 0.001f;
        key_params->map->camera->pitch -= (key_params->map->camera->mouse->last_pos.y - y) * 0.001f;
        //avoid mouse to go out of the window
        if (x < 0)
            mlx_mouse_move(key_params->win->mlx_ptr, key_params->win->win_ptr, 0, y);
        else if (x > SCREEN_WIDTH)
            mlx_mouse_move(key_params->win->mlx_ptr, key_params->win->win_ptr, SCREEN_WIDTH, y);
        ft_refresh_window(key_params->win, key_params->map);
    }
    key_params->map->camera->mouse->last_pos.x = x;
    key_params->map->camera->mouse->last_pos.y = y;
    return (0);
}