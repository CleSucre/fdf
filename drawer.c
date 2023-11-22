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
void ft_draw_line(t_win *data, t_vector2 point1, t_vector2 point2) {
    t_vector2   delta;
    t_vector2   currentPoint;
    int         steps;
    int         i;

    //printf("drawing line:\n1x: %f\n1y: %f\n2x: %f\n2y: %f\n", point1.pos.x, point1.pos.y, point2.pos.x, point2.pos.y);
    delta.x = point2.x - point1.x;
    delta.y = point2.y - point1.y;
    steps = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
    i = 0;
    while (i < steps)
    {
        float t = (float)i / (float)steps;
        currentPoint.x = point1.x + (delta.x * t);
        currentPoint.y = point1.y + (delta.y * t);
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, currentPoint.x, currentPoint.y, MAP_COLOR);
        i++;
    }
}

void    ft_draw_map(t_win *win, t_map *map)
{
    int i;
    int j;
    t_vector2   tmp1;
    t_vector2   tmp2;
    
    //ft_draw_line(&win, ft_make_vector2(0, 0), ft_make_vector2(200, 200));
    i = 0;
    while (i < map->maxY)
    {
        j = 0;
        while (j < map->maxX)
        {
            /*
            if (j + 1 < map->maxX)
            {
                tmp1 = ft_3dto2d(map->map[i][j], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                tmp2 = ft_3dto2d(map->map[i][j + 1], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                ft_draw_line(
                    win,
                    tmp1,
                    tmp2
                );
            }
            if (i + 1 < map->maxY)
            {
                //ft_printf("using matrix Y %d %d\n", i + 1, j);
                tmp1 = ft_3dto2d(map->map[i][j], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                tmp2 = ft_3dto2d(map->map[i + 1][j], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                ft_draw_line(
                    win,
                    tmp1,
                    tmp2
                );
            }
            */
            if (j + 1 < map->maxX)
            {
                tmp1 = ft_3dto2d(map->map[i][j], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                if (tmp1.x != 0 && tmp1.y != 0)
                {
                    tmp2 = ft_3dto2d(map->map[i][j + 1], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                    if (tmp2.x != 0 && tmp2.y != 0)
                    {
                        ft_draw_line(
                            win,
                            tmp1,
                            tmp2
                        );
                    }
                }
            }
            if (i + 1 < map->maxY)
            {
                //ft_printf("using matrix Y %d %d\n", i + 1, j);
                tmp1 = ft_3dto2d(map->map[i][j], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                if (tmp1.x != 0 && tmp1.y != 0)
                {
                    tmp2 = ft_3dto2d(map->map[i + 1][j], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
                    if (tmp2.x != 0 && tmp2.y != 0)
                    {
                        ft_draw_line(
                            win,
                            tmp1,
                            tmp2
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
    mlx_clear_window(win->mlx_ptr, win->win_ptr);
    ft_draw_map(win, map);
}   
