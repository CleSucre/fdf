/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:36 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 14:47:36 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    ft_debug_vector2(t_vector2 vector2)
{
    ft_printf("(%f,%f)", vector2.x, vector2.y);
}

void    ft_debug_vector3(t_vector3 vector3)
{
    ft_printf("(%f,%f,%f)", vector3.x, vector3.y, vector3.z);
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
            ft_debug_vector3(map->map[i][j]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}
