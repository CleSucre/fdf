/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_maker_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:19:34 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 02:09:36 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	ft_init_x(t_map *map, int i, char **positions)
{
	float	y;
	int		j;

	j = 0;
	while (positions[j] && j < map->size_x)
	{
		y = ft_atoi(positions[j]) + 1;
		map->map_vector3[i][j].x = j;
		map->map_vector3[i][j].y = y;
		map->map_vector3[i][j].z = i;
		if (y > map->size_y)
			map->size_y = y;
		free(positions[j]);
		j++;
	}
	free(positions);
}

static void	ft_alloc_map(t_map *map)
{
	map->line = malloc(sizeof(t_line));
	if (map->line == NULL)
		return ;
	map->line->point1 = malloc(sizeof(t_vector2));
	if (map->line->point1 == NULL)
	{
		free(map->line);
		return ;
	}
	map->line->point2 = malloc(sizeof(t_vector2));
	if (map->line->point2 == NULL)
	{
		free(map->line->point1);
		free(map->line);
		return ;
	}
	map->text = malloc(sizeof(char) * 9);
	if (map->text == NULL)
	{
		free(map->line->point1);
		free(map->line->point2);
		free(map->line);
		return ;
	}
}

static t_map	*ft_init_map(int maxX, int maxZ)
{
	t_map	*map;
	int		i;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->map_vector3 = (t_vector3 **)malloc(sizeof(t_vector3 *) * (maxZ));
	if (map->map_vector3 == NULL)
	{
		free(map);
		return (NULL);
	}
	i = -1;
	while (++i < maxZ)
	{
		map->map_vector3[i] = (t_vector3 *)malloc(sizeof(t_vector3) * (maxX));
		if (map->map_vector3[i] == NULL)
			return (ft_free_map(map));
	}
	map->size_x = maxX;
	map->size_y = 0;
	map->size_z = maxZ;
	return (map);
}

static t_map	*create_map_from_lines(char **lines)
{
	int		i;
	t_map	*map;
	char	**positions;

	i = ft_strlentab((const char **)lines);
	map = ft_init_map(ft_count_words(lines[0], " "), i);
	i = -1;
	while (++i < map->size_z && lines[i])
	{
		positions = ft_split(lines[i], " ");
		ft_init_x(map, i, positions);
		free(lines[i]);
	}
	free(lines);
	map->transformed_point1 = malloc(sizeof(t_vector3));
	if (map->transformed_point1 == NULL)
		return (ft_free_map(map));
	map->transformed_point2 = malloc(sizeof(t_vector3));
	if (map->transformed_point2 == NULL)
	{
		free(map->transformed_point1);
		return (ft_free_map(map));
	}
	ft_alloc_map(map);
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
	map->camera = ft_init_camera(map);
	return (map);
}
