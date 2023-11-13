/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:38:51 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/13 09:38:51 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int action_window(int keycode, t_data *data)
{
    //ft_printf("action_window keycode = %u\n", keycode);
    if (keycode == 65307)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        exit(0);
    }
    return (0);
}

t_vector2 ft_3dto2d(t_vector3 pos, t_vector3 viewPos, t_vector3 viewPosProjection, int screenWidth, int screenHeight)
{
    t_vector2 result;

    result.x = (pos.x - viewPos.x) * (viewPosProjection.z / (pos.z - viewPos.z)) + viewPosProjection.x;
    result.y = (pos.y - viewPos.y) * (viewPosProjection.z / (pos.z - viewPos.z)) + viewPosProjection.y;

    result.x = result.x * screenWidth / viewPosProjection.z;
    result.y = result.y * screenHeight / viewPosProjection.z;

    return (result);
}

void    ft_draw_line(t_data *data, t_vector2 *pos1, t_vector2 *pos2)
{
    int     i;
    float   t;
    int     steps;
    t_vector2 currentPoint;

    i = 0;
    steps = sqrt(pow(pos2->x - pos1->x, 2) + pow(pos2->y - pos1->y, 2));
    while (++i <= steps) {
        t = (float)i / steps;
        currentPoint.x = pos1->x + t * (pos2->x - pos1->x);
        currentPoint.y = pos1->y + t * (pos2->y - pos1->y);
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, currentPoint.x, currentPoint.y, MAP_COLOR);
    }
}

int ft_draw_map(t_data *data)
{
    t_vector2   pos1;
    t_vector2   pos2;
    int         points[3][3] = {
        {0, 0, 0},
        {0, 10, 0},
        {0, 0, 0},
    };
    int     maxX = 3;
    int     maxY = 3;
    int     x;
    int     y;

    x = 0;
    y = 0;
    while (x <= maxX && y <= maxY)
    {
        if (x < maxX)
        {
            pos1.x = points[x][y];
            pos1.y = points[x][y];
            pos2.x = points[x + 1][y];
            pos2.y = points[x + 1][y];
            ft_draw_line(data, pos1, pos2);
        }
        if (y < maxY)
        {
            ft_draw_line(data, &points[x][y], &points[x][y + 1]);
        }
        x++;
        y++;
    }
}