/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:47:26 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 14:47:26 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Draw a pixel on an image
 * @param win
 * @param point
 * @param color
 */
void	ft_draw_pixel(t_win *win, t_vector2 point, int color)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*img;

	img = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
	if ((int)point.x >= 0 && (int)point.x < SCREEN_WIDTH && (int)point.y >= 0
		&& (int)point.y < SCREEN_HEIGHT)
		*(int *)(img + ((int)point.x * bpp / 8) + ((int)point.y
					* size_line)) = color;
}

/**
 * @brief Draw a line between two points on an image
 *
 * @param win
 * @param point1
 * @param point2
 */
void	ft_draw_line(t_win *win, t_line line)
{
	t_vector2	delta;
	t_vector2	current_point;
	int			steps;
	int			i;
	float		t;

	delta.x = line.point2.x - line.point1.x;
	delta.y = line.point2.y - line.point1.y;
	steps = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	i = 0;
	while (i < steps)
	{
		t = (float)i / (float)steps;
		current_point.x = line.point1.x + (delta.x * t);
		current_point.y = line.point1.y + (delta.y * t);
		ft_draw_pixel(win, current_point,
			ft_get_color_between_two(line.point1_color, line.point2_color, t));
		i++;
	}
}

/**
 * @brief Reset the image to black
 *
 * @param win
 */
void	ft_reset_image(t_win *win)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*img;

	img = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
	ft_bzero(img, SCREEN_WIDTH * SCREEN_HEIGHT * (bpp / 8));
}

void	ft_refresh_window(t_win *win, t_map *map)
{
	ft_reset_image(win);
	ft_draw_2d_map(map, map->camera, win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
