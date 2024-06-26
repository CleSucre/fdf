/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:55:37 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 06:53:15 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_free_program(t_key_params *params)
{
	mlx_destroy_image(params->win->mlx_ptr, params->win->img_ptr);
	mlx_clear_window(params->win->mlx_ptr, params->win->win_ptr);
	mlx_destroy_window(params->win->mlx_ptr, params->win->win_ptr);
	mlx_destroy_display(params->win->mlx_ptr);
	free(params->win->mlx_ptr);
	free(params->win);
	ft_free_map(params->map);
	free(params);
	exit(0);
}

void	*ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size_z)
	{
		free(map->map_vector3[i]);
		i++;
	}
	free(map->map_vector3);
	free(map->camera);
	free(map->line->point1);
	free(map->line->point2);
	free(map->line);
	free(map->text);
	free(map->transformed_point1);
	free(map->transformed_point2);
	free(map);
	return (NULL);
}
