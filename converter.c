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

t_vector2   ft_3dto2d(t_vector3 point, t_camera camera, int screenWidth, int screenHeight, int force)
{
    (void)force;
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
    if (fabs(point.x) <= 2.0f && fabs(point.y) <= 2.0f && force == 0) {
        projectedPoint.x = (point.x + 1.0f) * 0.5f * screenWidth;
        projectedPoint.y = (1.0f - point.y) * 0.5f * screenHeight;
    } else {
        // If the point is outside the frustum, return null*
        projectedPoint.x = 0;
        projectedPoint.y = 0;
    }
    /*
    projectedPoint.x = (point.x + 1.0f) * 0.5f * screenWidth;
    projectedPoint.y = (1.0f - point.y) * 0.5f * screenHeight;
    */

    return (projectedPoint);
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
    ft_printf("maxX = %d\nmaxY = %d\n", map->maxX, map->maxY);
    i = 0;
    while (lines[i] && i < map->maxY)
    {
        positions = ft_split(lines[i], ' ');
        j = 0;
        while (positions[j] && j < map->maxX)
        {
            tz = ft_atoi(positions[j]) + 1;
            map->map[i][j] = ft_make_vector3(j, tz, i);
            ft_debug_vector3(map->map[i][j]);
            j++;
        }
        i++;
    }
    //ft_debug_map(map);
    return (map);
}
