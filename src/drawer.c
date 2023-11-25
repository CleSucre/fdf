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

static int ft_get_color_between_two(int color1, int color2, float t)
{
    int r;
    int g;
    int b;

    r = (int)((float)((color2 & 0xFF0000) >> 16) * t) + (int)((float)((color1 & 0xFF0000) >> 16) * (1 - t));
    g = (int)((float)((color2 & 0x00FF00) >> 8) * t) + (int)((float)((color1 & 0x00FF00) >> 8) * (1 - t));
    b = (int)((float)((color2 & 0x0000FF)) * t) + (int)((float)((color1 & 0x0000FF)) * (1 - t));
    return ((r << 16) + (g << 8) + b);
}

/**
 * @brief Get the color from the y coordinate
 * @param y
 * @return int
 */
int ft_get_color_from_y(int y, int max_y, int min_y)
{
    if (y < min_y)
        return (HEX_BLUE);
    if (y > max_y)
        return (HEX_RED);
    return (ft_get_color_between_two(HEX_BLUE, HEX_RED, (float)(y - min_y) / (float)(max_y - min_y)));
}

/**
 * @brief Draw a pixel on an image
 * @param win
 * @param point
 * @param color
 */
void    ft_draw_pixel(t_win *win, t_vector2 point, int color)
{
    int     bpp;
    int     size_line;
    int     endian;
    char    *img;

    img = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
    if ((int)point.x >= 0 && (int)point.x < SCREEN_WIDTH && (int)point.y >= 0 && (int)point.y < SCREEN_HEIGHT)
        *(int *)(img + ((int)point.x * bpp / 8) + ((int)point.y * size_line)) = color;
}

/**
 * @brief Draw a line between two points on an image
 *
 * @param win
 * @param point1
 * @param point2
 */
void    ft_draw_line(t_win *win, t_line line) {
    t_vector2   delta;
    t_vector2   currentPoint;
    int         steps;
    int         i;
    float       t;

    delta.x = line.point2.x - line.point1.x;
    delta.y = line.point2.y - line.point1.y;
    steps = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
    i = 0;
    while (i < steps)
    {
        t = (float)i / (float)steps;
        currentPoint.x = line.point1.x + (delta.x * t);
        currentPoint.y = line.point1.y + (delta.y * t);
        ft_draw_pixel(win, currentPoint, ft_get_color_between_two(line.point1_color, line.point2_color, t));
        i++;
    }
}

/**
 * @brief Reset the image to black
 *
 * @param win
 */
void    ft_reset_image(t_win *win)
{
    int     bpp;
    int     size_line;
    int     endian;
    char    *img;

    img = mlx_get_data_addr(win->img_ptr, &bpp, &size_line, &endian);
    ft_bzero(img, SCREEN_WIDTH * SCREEN_HEIGHT * (bpp / 8));
}

void ft_refresh_window(t_win *win, t_map *map)
{
    ft_reset_image(win);
    ft_draw_2d_map(map, map->camera, win);
    mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
