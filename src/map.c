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
	map->line->point1 = map->point1;
	map->line->point2 = map->point2;
	map->line->point1_color = ft_get_color_from_y(
			map->map_vector3[i][j].y, map->size_y, 0);
	map->line->point2_color = ft_get_color_from_y(
			map->map_vector3[i][j + 1].y, map->size_y, 0);
	ft_draw_line(win, map->line);
}

static void	ft_pregen_horizontal_line(t_map *map, t_win *win, int i, int j)
{
	if (j + 1 >= map->size_x)
		return ;
	if (map->map_vector3[i][j].z >= 0 && map->map_vector3[i][j + 1].z >= 0)
	{
		ft_projet_vector3(map->point1, map->map_vector3[i][j], map->camera);
		ft_projet_vector3(map->point2, map->map_vector3[i][j + 1], map->camera);
		if (ft_check_frustum(map->point1))
			ft_gen_horizontal_line(map, win, i, j);
		else if (ft_check_frustum(map->point2))
			ft_gen_horizontal_line(map, win, i, j);
	}
}

static void	ft_gen_vertical_line(t_map *map, t_win *win, int i, int j)
{
	map->line->point1 = map->point1;
	map->line->point2 = map->point2;
	map->line->point1_color = ft_get_color_from_y(
			map->map_vector3[i][j].y, map->size_y, 0);
	map->line->point2_color = ft_get_color_from_y(
			map->map_vector3[i + 1][j].y, map->size_y, 0);
	ft_draw_line(win, map->line);
}

static void	ft_pregen_vertical_line(t_map *map, t_win *win, int i, int j)
{
	if (i + 1 >= map->size_z)
		return ;
	if (map->map_vector3[i][j].z >= 0 && map->map_vector3[i + 1][j].z >= 0)
	{
		ft_projet_vector3(map->point1, map->map_vector3[i][j], map->camera);
		ft_projet_vector3(map->point2, map->map_vector3[i + 1][j], map->camera);
		if (ft_check_frustum(map->point1))
			ft_gen_vertical_line(map, win, i, j);
		else if (ft_check_frustum(map->point2))
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
			ft_pregen_horizontal_line(map, win, i, j);
			ft_pregen_vertical_line(map, win, i, j);
			j++;
		}
		i++;
	}
}
