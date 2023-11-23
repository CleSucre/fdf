/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:38:51 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/13 09:38:51 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_vector2 ft_3dto2d(t_vector3 point, t_camera camera, int screenWidth, int screenHeight) {
    // Translation du point par rapport à la position de la caméra
    point.x -= camera.pos.x;
    point.y -= camera.pos.y;
    point.z -= camera.pos.z;

    // Rotation du point autour des axes x, y
    float cosYaw = cosf(camera.yaw);
    float sinYaw = sinf(camera.yaw);
    float cosPitch = cosf(camera.pitch);
    float sinPitch = sinf(camera.pitch);

    float newX = point.x * cosYaw - point.z * sinYaw;
    float newZ = point.x * sinYaw + point.z * cosYaw;
    point.x = newX;
    point.z = newZ;

    float newY = point.y * cosPitch - point.z * sinPitch;
    float newZ2 = point.y * sinPitch + point.z * cosPitch;
    point.y = newY;
    point.z = newZ2;

    // Projection du point sur le plan 2D
    float distance = point.z;
    point.x /= distance;
    point.y /= distance;

    // Application du champ de vision (fov)
    float screenDistance = tanf(camera.fov * 0.5f);
    point.x /= screenDistance;
    point.y /= screenDistance;

    // Mappage des coordonnées 2D à l'écran
    t_vector2 projectedPoint;

    // Check if the point is within the normalized device coordinates
    if (fabs(point.x) <= 1.0f && fabs(point.y) <= 1.0f) {
        projectedPoint.x = (point.x + 1.0f) * 0.5f * screenWidth;
        projectedPoint.y = (1.0f - point.y) * 0.5f * screenHeight;
    } else {
        // If the point is outside the frustum, return a null vector
        projectedPoint.x = projectedPoint.y = 0.0f;
    }

    return projectedPoint;
}

void    ft_convert_to_map_vector2(t_map *map)
{
    t_vector2   **map_vector2;
    int         i;
    int         j;

    map_vector2 = (t_vector2 **)malloc(sizeof(t_vector2 *) * map->sizeY);
    if (map_vector2 == NULL)
    {
        ft_printf("malloc error in ft_make_map_vector2\n");
        exit(0);
    }
    i = 0;
    while (i < map->sizeY)
    {
        map_vector2[i] = (t_vector2 *)malloc(sizeof(t_vector2) * map->sizeX);
        if (map_vector2[i] == NULL)
        {
            ft_printf("malloc error in ft_make_map_vector2\n");
            exit(0);
        }
        j = 0;
        while (j < map->sizeX)
        {
            map_vector2[i][j] = ft_3dto2d(map->map[i][j], map->camera, SCREEN_WIDTH, SCREEN_HEIGHT);
            j++;
        }
        i++;
    }
    map->map_vector2 = map_vector2;
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
    map = ft_init_map(ft_count_words(lines[0], ' '), i);
    ft_printf("maxX = %d\nmaxY = %d\n", map->sizeX, map->sizeY);
    i = 0;
    while (lines[i] && i < map->sizeY)
    {
        positions = ft_split(lines[i], ' ');
        j = 0;
        while (positions[j] && j < map->sizeX)
        {
            tz = ft_atoi(positions[j]) + 1;
            map->map[i][j] = ft_make_vector3(j, tz, i);
            j++;
        }
        i++;
    }
    map->camera = ft_make_camera(ft_make_vector3(map->sizeX * 2, map->sizeY * 3, map->sizeX * 2), 7, 0.5, 100);
    map->refresh_window = ft_refresh_window;
    ft_convert_to_map_vector2(map);
    return (map);
}
