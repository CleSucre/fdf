/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:16:35 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 06:53:17 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_pixel(t_win *win, t_vector2 point, int color)
{
	if ((int)point.x >= 0 && (int)point.x < SCREEN_WIDTH && (int)point.y >= 0
		&& (int)point.y < SCREEN_HEIGHT)
		*(int *)(win->img_data + ((int)point.x * win->bpp / 8) + ((int)point.y
					* win->size_line)) = color;
}

void	ft_draw_line(t_win *win, t_line *line)
{
	t_vector2	delta;
	t_vector2	current_point;
	int			steps;
	int			i;
	int			color;

	delta.x = line->point2->x - line->point1->x;
	delta.y = line->point2->y - line->point1->y;
	if (abs((int)delta.x) > abs((int)delta.y))
		steps = abs((int)delta.x);
	else
		steps = abs((int)delta.y);
	color = ft_get_color_between_two(line->point1_color, line->point2_color, 0);
	i = 0;
	while (i <= steps)
	{
		current_point.x = line->point1->x + (delta.x * i) / steps;
		current_point.y = line->point1->y + (delta.y * i) / steps;
		ft_draw_pixel(win, current_point, color);
		i++;
	}
}

void	ft_refresh_window(t_win *win, t_map *map)
{
	ft_memset(win->img_data, 0, win->img_size);
	ft_draw_map(map, win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
