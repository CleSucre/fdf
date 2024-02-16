/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:37:03 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/29 00:37:05 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_map	*create_map_from_lines(char **lines)
{
	int		i;
	int		j;
	float	tz;
	t_map	*map;
	char	**positions;

	i = 0;
	while (lines[i])
		i++;
	map = ft_init_map(ft_count_words(lines[0], ' '), i);
	i = 0;
	while (lines[i] && i < map->size_z)
	{
		positions = ft_split(lines[i], ' ');
		j = 0;
		while (positions[j] && j < map->size_x)
		{
			tz = ft_atoi(positions[j]) + 1;
			map->map_vector3[i][j] = ft_make_vector3(j, tz, i);
			if (tz > map->size_y)
				map->size_y = tz;
			free(positions[j]);
			j++;
		}
		free(positions);
		free(lines[i]);
		i++;
	}
	free(lines);
	return (map);
}

t_map	*ft_get_map_from_file(int fd)
{
	char	**lines;
	t_map	*map;

	lines = get_lines(fd);
	if (lines == NULL)
		return (NULL);
	map = create_map_from_lines(lines);
	ft_printf("x %d, y %d, z %d\n", map->size_x, map->size_y, map->size_z);
	map->camera = ft_init_camera(
			ft_make_vector3(0, 25, 0));
	map->refresh_window = ft_refresh_window;
	return (map);
}

/**
 * @brief Draws a line between two points in a 2D window.
 *
 * @param map Environment information.
 * @param camera Camera information.
 */
void	ft_draw_2d_map(t_map *map, t_camera *camera, t_win *win)
{
	int			i;
	int			j;
	t_vector2	*point1;
	t_vector2	*point2;

	point1 = (t_vector2 *)malloc(sizeof(t_vector2));
	if (point1 == NULL)
		return ;
	point2 = (t_vector2 *)malloc(sizeof(t_vector2));
	if (point2 == NULL)
	{
		free(point1);
		return ;
	}
	i = 0;
	while (i < map->size_z)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (j + 1 < map->size_x)
			{
				*point1 = ft_3d_to_2d(map->map_vector3[i][j], camera);
				*point2 = ft_3d_to_2d(map->map_vector3[i][j + 1], camera);
				ft_draw_line(win, ft_make_line(*point1, *point2,
						ft_get_color_from_y(map->map_vector3[i][j].y,
							map->size_y, 0),
						ft_get_color_from_y(map->map_vector3[i][j + 1].y,
							map->size_y, 0)));
			}
			if (i + 1 < map->size_z)
			{
				*point1 = ft_3d_to_2d(map->map_vector3[i][j], camera);
				*point2 = ft_3d_to_2d(map->map_vector3[i + 1][j], camera);
				ft_draw_line(win, ft_make_line(*point1, *point2,
						ft_get_color_from_y(map->map_vector3[i][j].y,
							map->size_y, 0),
						ft_get_color_from_y(map->map_vector3[i + 1][j].y,
							map->size_y, 0)));
			}
			j++;
		}
		i++;
	}
	free(point1);
	free(point2);
}
