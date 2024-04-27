/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:16:35 by julthoma          #+#    #+#             */
/*   Updated: 2024/04/24 16:16:35 by julthoma         ###   ########.fr       */
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

static void	ft_draw_text(t_win *win, t_map *map, double cpu_time_used)
{
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 10, 0xFFFFFF,
		"Camera position:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 30, 0xFFFFFF, "x:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 30, 30, 0xFFFFFF,
		ft_itoa(map->camera->position.x));
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 50, 0xFFFFFF, "y:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 30, 50, 0xFFFFFF,
		ft_itoa(map->camera->position.y));
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 70, 0xFFFFFF, "z:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 30, 70, 0xFFFFFF,
		ft_itoa(map->camera->position.z));
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 90, 0xFFFFFF, "Camera yaw:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 100, 90, 0xFFFFFF,
		ft_dtoa(map->camera->yaw, 5));
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 110, 0xFFFFFF,
		"Camera pitch:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 100, 110, 0xFFFFFF,
		ft_dtoa(map->camera->pitch, 5));
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 130, 0xFFFFFF,
		"Refresh speed:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 100, 130, 0xFFFFFF,
		ft_dtoa(cpu_time_used, 6));
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
	if (abs(delta.x) > abs(delta.y))
		steps = abs(delta.x);
	else
		steps = abs(delta.y);
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
	clock_t	start;

	start = clock();
	ft_reset_image(win);
	ft_draw_map(map, win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	ft_draw_text(win, map, ((double)(clock() - start)) / CLOCKS_PER_SEC);
}
