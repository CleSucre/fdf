/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:26 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 14:47:26 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Fonction de dessin de ligne à partir de deux vecteurs 2D
void ft_draw_line(void *mlx_ptr, void *win_ptr, t_vector2 point1, t_vector2 point2) {
    t_vector2   delta;
    t_vector2   currentPoint;
    int         steps;
    int         i;

    //printf("drawing line:\n1x: %f\n1y: %f\n2x: %f\n2y: %f\n", point1.pos.x, point1.pos.y, point2.pos.x, point2.pos.y);
    delta.x = point2.x - point1.x;
    if (delta.x >= SCREEN_HEIGHT || delta.x <= -SCREEN_HEIGHT)
    {
        return ;
    }
    delta.y = point2.y - point1.y;
    if (delta.y >= SCREEN_HEIGHT || delta.y <= -SCREEN_HEIGHT)
    {
        return ;
    }
    steps = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
    i = 0;
    while (i < steps)
    {
        float t = (float)i / (float)steps;
        currentPoint.x = point1.x + (delta.x * t);
        currentPoint.y = point1.y + (delta.y * t);
        mlx_pixel_put(mlx_ptr, win_ptr, currentPoint.x, currentPoint.y, MAP_COLOR);
        i++;
    }
}

void    ft_draw_map(t_win *win, t_map *map)
{
    int i;
    int j;
    void    *mlx_ptr;

    if (win->ptr_use == FALSE)
    {
        mlx_ptr = win->mlx_ptr;
        win->ptr_use = TRUE;
    }
    else
    {
        mlx_ptr = win->mlx_ptr2;
        win->ptr_use = FALSE;
    }
    
    //set do_flush to 0 in mlx_loop_hook to avoid flickering
    i = 0;
    while (i < map->maxY)
    {
        j = 0;
        while (j < map->maxX)
        {
            if (j + 1 < map->maxX)
            {
                if (map->map_vector2[i][j].x != 0 && map->map_vector2[i][j].y != 0)
                {
                    if (map->map_vector2[i][j + 1].x != 0 && map->map_vector2[i][j + 1].y != 0)
                    {
                        ft_draw_line(
                            mlx_ptr,
                            win->win_ptr,
                            map->map_vector2[i][j],
                            map->map_vector2[i][j + 1]
                        );
                    }
                }
            }
            if (i + 1 < map->maxY)
            {
                if (map->map_vector2[i][j].x != 0 && map->map_vector2[i][j].y != 0)
                {
                    if (map->map_vector2[i + 1][j].x != 0 && map->map_vector2[i + 1][j].y != 0)
                    {
                        ft_draw_line(
                            mlx_ptr,
                            win->win_ptr,
                            map->map_vector2[i][j],
                            map->map_vector2[i + 1][j]
                        );
                    }
                }
            }
            j++;
        }
        i++;
    }
}

void ft_refresh_window(t_win *win, t_map *map)
{
    void    *mlx_ptr_to_clear;
    ft_convert_to_map_vector2(map);
    if (win->ptr_use == FALSE)
    {
        mlx_ptr_to_clear = win->mlx_ptr2;
        win->ptr_use = TRUE;
    }
    else
    {
        mlx_ptr_to_clear = win->mlx_ptr;
        win->ptr_use = FALSE;
    }
    mlx_clear_window(mlx_ptr_to_clear, win->win_ptr);
    ft_draw_map(win, map);
}
