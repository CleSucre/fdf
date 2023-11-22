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

int action_window(int keycode, t_win *data)
{
    ft_printf("action_window keycode = %u\n", keycode);
    if (keycode == 65307)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        exit(0);
    }
    return (0);
}

t_vector2 ft_3dto2d(t_vector3 pos, t_vector3 viewPos, t_vector3 viewPosProjection, int screenWidth, int screenHeight)
{
    t_vector2   result;
    float       scale;

    printf("convert 3d to 2d:\n");
    printf("pos.x = %f\npos.y = %f\npos.z = %f\n", pos.x, pos.y, pos.z);
    pos.x -= viewPos.x;
    pos.y -= viewPos.y;
    pos.z -= viewPos.z;
    // Projection de la position sur le plan de projection
    scale = viewPosProjection.z / pos.z;
    result.x = pos.x * scale + screenWidth / 2;
    result.y = -pos.y * scale + screenHeight / 2;  // Inversion de l'axe y pour correspondre à la convention d'écran
    printf("result.x = %f\nresult.y = %f\n", result.x, result.y);
    return (result);
}

/*
void    ft_draw_line(t_win *data, t_vector2 pos1, t_vector2 pos2)
{
    int     i;
    float   t;
    int     steps;
    t_vector2 currentPoint;

    //printf("drawing line:\n1x: %f\n1y: %f\n2x: %f\n2y: %f\n", pos1.x, pos1.y, pos2.x, pos2.y);
    i = 0;
    steps = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2));
    while (i < steps)
    {
        t = (float)i / (float)steps;
        currentPoint.x = pos1.x + (pos2.x - pos1.x) * t;
        currentPoint.y = pos1.y + (pos2.y - pos1.y) * t;
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, currentPoint.x, currentPoint.y, MAP_COLOR);
        i++;
    }
}
*/

void ft_draw_line(t_win *data, t_vector2 pos1, t_vector2 pos2)
{
    int dx = abs(pos2.x - pos1.x);
    int dy = abs(pos2.y - pos1.y);
    int sx = (pos1.x < pos2.x) ? 1 : -1;
    int sy = (pos1.y < pos2.y) ? 1 : -1;
    int err = dx - dy;
    while (1)
    {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, pos1.x, pos1.y, MAP_COLOR);
        if (pos1.x == pos2.x && pos1.y == pos2.y)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            pos1.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            pos1.y += sy;
        }
    }
}

t_vector3   ft_make_vector3(float x, float y, float z)
{
    t_vector3 vector3;

    vector3.x = x;
    vector3.y = y;
    vector3.z = z;
    return (vector3);
}

t_vector2   ft_make_vector2(float x, float y)
{
    t_vector2 vector2;

    vector2.x = x;
    vector2.y = y;
    return (vector2);
}

t_map   *ft_init_map(int maxX, int maxY)
{
    t_map   *map;
    int    i;

    map = (t_map *)malloc(sizeof(t_map));
    if (map == NULL)
        return (NULL);
    map->map = (t_vector2 **)malloc(sizeof(t_vector2 *) * maxY);
    if (map->map == NULL)
    {
        free(map);
        return (NULL);
    }
    i = 0;
    while (i < maxY)
    {
        map->map[i] = (t_vector2 *)malloc(sizeof(t_vector2) * maxX);
        if (map->map[i] == NULL)
        {
            while (i > 0)
                free(map->map[--i]);
            free(map->map);
            free(map);
            return (NULL);
        }
        i++;
    }
    map->maxX = maxX;
    map->maxY = maxY;
    return (map);
}

t_map   *ft_get_map_from_file(int fd)
{
    t_map       *map;
    char        **lines;
    char        **positions;
    int         i;
    int         j;
    float       tz;

    lines = get_lines(fd);
    if (lines == NULL)
        return (NULL);
    i = 0;
    while (lines[i])
    {
        ft_printf("%s\n", lines[i]);
        i++;
    }
    map = ft_init_map(i, ft_count_words(lines[0], ' '));
    ft_printf("maxX = %d\nmaxY = %d\n", map->maxX, map->maxY);
    i = 0;
    while (lines[i])
    {
        positions = ft_split(lines[i], ' ');
        j = 0;
        while (positions[j])
        {
            tz = ft_atoi(positions[j]) + 1;
            map->map[i][j] = ft_3dto2d(
                ft_make_vector3(j, i, tz),
                ft_make_vector3(0, 0, 0), //camera position
                ft_make_vector3(0, 0, 10.0f), //camera position projection
                500,
                500
            );
            j++;
        }
        i++;
    }
    return (map);
}

void    ft_debug_map(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->maxY)
    {
        j = 0;
        while (j < map->maxX)
        {
            printf("(%f,%f)", map->map[i][j].x, map->map[i][j].y);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}

int ft_draw_map(t_win win, t_map *map)
{
    int i;
    int j;

    ft_debug_map(map);
    i = 0;
    while (i < map->maxY)
    {
        j = 0;
        while (j < map->maxX)
        {
            //ft_printf("i = %d, j = %d\n", i, j);
            if (j + 1 < map->maxX)
                ft_draw_line(&win, map->map[i][j], map->map[i][j + 1]);
            if (i + 1 < map->maxY)
                ft_draw_line(&win, map->map[i][j], map->map[i + 1][j]);
            j++;
        }
        i++;
    }
    return (0);
}