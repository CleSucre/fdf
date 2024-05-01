/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:16:35 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 02:09:22 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_draw_pixel(t_win *win, t_vector2 point, int color)
{
	if ((int)point.x >= 0 && (int)point.x < SCREEN_WIDTH && (int)point.y >= 0
		&& (int)point.y < SCREEN_HEIGHT)
		*(int *)(win->img_data + ((int)point.x * win->bpp / 8) + ((int)point.y
					* win->size_line)) = color;
}

static void	ft_draw_text_2(t_win *win, t_map *map)
{
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 10, 0xFFFFFF,
		"Camera position:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 30, 0xFFFFFF, "x:");
	ft_setitoa(map->text, map->camera->position.x);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 30, 30, 0xFFFFFF, map->text);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 50, 0xFFFFFF, "y:");
	ft_setitoa(map->text, map->camera->position.y);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 30, 50, 0xFFFFFF, map->text);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 70, 0xFFFFFF, "z:");
	ft_setitoa(map->text, map->camera->position.z);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 30, 70, 0xFFFFFF, map->text);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 90, 0xFFFFFF, "Camera yaw:");
	ft_setdtoa(map->text, map->camera->yaw, 5);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 150, 90, 0xFFFFFF, map->text);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 110, 0xFFFFFF,
		"Camera pitch:");
	ft_setdtoa(map->text, map->camera->pitch, 5);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 150, 110, 0xFFFFFF, map->text);
}

static void	ft_draw_text(t_win *win, t_map *map, double cpu_time_used)
{
	ft_draw_text_2(win, map);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 130, 0xFFFFFF,
		"Generation speed (ms):");
	ft_setdtoa(map->text, cpu_time_used, 3);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 150, 130, 0xFFFFFF, map->text);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 10, 150, 0xFFFFFF,
		"Generation count:");
	ft_setitoa(map->text, win->gen_count);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 150, 150, 0xFFFFFF, map->text);
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
	clock_t	current_time;
	double	time_difference;

	current_time = clock();
	time_difference = ((double)(current_time - win->last_refresh))
		/ CLOCKS_PER_SEC;
	if (time_difference < 0.00002)
		return ;
	win->gen_count++;
	ft_reset_image(win);
	ft_draw_map(map, win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	ft_draw_text(win, map, ((double)(clock() - current_time)) / CLOCKS_PER_SEC);
	win->last_refresh = clock();
}
