/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:35:18 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/13 09:35:18 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "key_map.h"

t_win  ft_init_window(char *filename)
{
    t_win win;

    win.mlx_ptr = mlx_init();
    win.win_ptr = mlx_new_window(win.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, filename);
    return (win);
}

void    ft_init_keymap(t_win *win, t_map *map)
{
    t_key_params    *params;

    params = (t_key_params*)malloc(sizeof(t_key_params));
    if (params == NULL)
    {
        ft_printf("malloc error in ft_init_keymap\n");
        exit(0);
    }
    params->win = win;
    params->map = map;
    //wtf is this?
    mlx_hook(win->win_ptr, 2, 1L<<0, action_window, params);
}

int    ft_fdf(char *filename)
{
    t_map       *map;
    t_camera    camera;
    int         fd;
    t_win       win;

    fd = open(filename, O_RDONLY);
    map = ft_get_map_from_file(fd);
    win = ft_init_window(filename);
    ft_init_keymap(&win, map);
    camera = ft_make_camera(
        ft_make_vector3(100, 100, 100),
        180,
        180,
        100
    );
    map->camera = camera;

    map->refresh_window = ft_refresh_window;
    ft_draw_map(&win, map);
    mlx_loop(win.mlx_ptr);

    close(fd);
    ft_free_map(map);
    mlx_destroy_window(win.mlx_ptr, win.win_ptr);
    free(win.mlx_ptr);
    free(win.win_ptr);
    return (0);
}