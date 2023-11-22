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
    win.win_ptr = mlx_new_window(win.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, filename);
    mlx_key_hook(win.win_ptr, action_window, &win);
    return (win);
}



int    ft_fdf(char *filename)
{
    t_map   *map;
    int     fd;
    t_win  win;

    fd = open(filename, O_RDONLY);
    map = ft_get_map_from_file(fd);
    win = ft_init_window(filename);
    
    ft_draw_map(win, map);
    mlx_loop(win.mlx_ptr);

    close(fd);
    ft_free_map(map);
    mlx_destroy_window(win.mlx_ptr, win.win_ptr);
    free(win.mlx_ptr);
    free(win.win_ptr);
    return (0);
}