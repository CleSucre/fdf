/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:50 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 14:47:50 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3   ft_get_vector3(int x, int y, int z)
{
    t_vector3   res;

    res.x = x;
    res.y = y;
    res.z = z;
    return (res);
}

void ft_free_vector3_map(t_vector3 **matrix, int maxY) {
    int i;

    i = 0;
    while (i < maxY)
        free(matrix[i++]);
    free(matrix);
}

void    ft_debug_vector3_matrix(t_vector3   **matrix, int maxX, int maxY) {
    int i;
    int j;

    (void)matrix;
    i = 0;
    while (i < maxX) {
        j = 0;
        while (j < maxY) {
            ft_printf("(%d, %d, %d) ", matrix[i][j].x, matrix[i][j].y, matrix[i][j].z);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}