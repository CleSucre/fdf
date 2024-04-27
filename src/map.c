/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:59:46 by julthoma          #+#    #+#             */
/*   Updated: 2024/04/27 04:59:46 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_gen_horizontal_line(t_map *map, t_win *win, int i, int j)
{
	map->line->point1_color = ft_get_color_from_y(
			map->map_vector3[i][j].y, map->size_y, 0);
	map->line->point2_color = ft_get_color_from_y(
			map->map_vector3[i][j + 1].y, map->size_y, 0);
	ft_draw_line(win, map->line);
}

static void	ft_pregen_horizontal_line(t_map *map, t_win *win, int i, int j)
{
	if (map->map_vector3[i][j].z >= 0 && map->map_vector3[i][j + 1].z >= 0)
	{
        transform_point(map->transformed_point1, &map->map_vector3[i][j], map->camera);
        transform_point(map->transformed_point2, &map->map_vector3[i][j + 1], map->camera);

		ft_projet_vector3(map->line->point1, map->transformed_point1, map->camera);
		ft_projet_vector3(map->line->point2, map->transformed_point2, map->camera);
		if (ft_check_frustum(map->transformed_point1) && ft_check_frustum(map->transformed_point2))
			ft_gen_horizontal_line(map, win, i, j);
	}
}

static void	ft_gen_vertical_line(t_map *map, t_win *win, int i, int j)
{
    map->line->point1_color = ft_get_color_from_y(
            map->map_vector3[i][j].y, map->size_y, 0);
    map->line->point2_color = ft_get_color_from_y(
            map->map_vector3[i + 1][j].y, map->size_y, 0);
    ft_draw_line(win, map->line);
}

static void	ft_pregen_vertical_line(t_map *map, t_win *win, int i, int j)
{
	if (map->map_vector3[i][j].z >= 0 && map->map_vector3[i + 1][j].z >= 0)
	{
        transform_point(map->transformed_point1, &map->map_vector3[i][j], map->camera);
        transform_point(map->transformed_point2, &map->map_vector3[i + 1][j], map->camera);

		ft_projet_vector3(map->line->point1, map->transformed_point1, map->camera);
		ft_projet_vector3(map->line->point2, map->transformed_point2, map->camera);
		if (ft_check_frustum(map->transformed_point1) && ft_check_frustum(map->transformed_point2))
			ft_gen_vertical_line(map, win, i, j);
	}
}

void	ft_draw_map(t_map *map, t_win *win)
{
	int			i;
	int			j;

	i = 0;
	while (i < map->size_z)
	{
		j = 0;
		while (j < map->size_x)
		{
            if (j + 1 < map->size_x)
    			ft_pregen_horizontal_line(map, win, i, j);
            if (i + 1 < map->size_z)
                ft_pregen_vertical_line(map, win, i, j);
			j++;
		}
		i++;
	}
}
