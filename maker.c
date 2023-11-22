/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:42 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 14:47:42 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_camera    ft_make_camera(t_vector3 pos, float yaw, float pitch, float fov)
{
    t_camera camera;
    
    camera.pos = pos;
    camera.yaw = yaw;
    camera.pitch = pitch;
    camera.fov = fov;
    return (camera);
}

t_map   *ft_init_map(int maxX, int maxY)
{
    t_map   *map;
    int    i;

    map = (t_map *)malloc(sizeof(t_map));
    if (map == NULL)
        return (NULL);
    map->map = (t_vector3 **)malloc(sizeof(t_vector3 *) * maxY);
    if (map->map == NULL)
    {
        free(map);
        return (NULL);
    }
    i = 0;
    while (i < maxY)
    {
        map->map[i] = (t_vector3 *)malloc(sizeof(t_vector3) * maxX);
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

void    ft_free_map(t_map *map)
{
    int i;

    i = 0;
    while (i < map->maxY)
    {
        free(map->map[i]);
        i++;
    }
    free(map->map);
    free(map);
}
