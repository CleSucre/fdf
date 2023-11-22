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

t_win  ft_init_window(char *filename)
{
    t_win win;

    win.mlx_ptr = mlx_init();
    win.win_ptr = mlx_new_window(win.mlx_ptr, 500, 500, filename);
    return (win);
}



int    ft_fdf(char *filename)
{
    t_map   *map;
    int     fd;
    t_win  win;
    //int         map[3][3] = {
    //    {0, 0, 0},
    //    {0, 10, 0},
    //    {0, 0, 0},
    //};
    //t_vector3   *points;
    //t_vector2  pos1;
    //t_vector2  pos2;

    win = ft_init_window(filename);
    mlx_key_hook(win.win_ptr, action_window, &win);

    /*
    pos1.x = 200;
    pos1.y = 200;

    pos2.x = 300;
    pos2.y = 200;

    ft_draw_line(&win, &pos1, &pos2);
    points = ft_get_points_from_map(map, 3, 3);
    */
    fd = open(filename, O_RDONLY);
    map = ft_get_map_from_file(fd);
    ft_draw_map(win, map);
    mlx_loop(win.mlx_ptr);
    close(fd);
    mlx_destroy_window(win.mlx_ptr, win.win_ptr);
    free(win.mlx_ptr);
    free(win.win_ptr);
    return (0);
}