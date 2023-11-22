/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 06:41:00 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/13 06:41:00 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/include/libft.h"
# include "libft/include/colors.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <fcntl.h>

# define MAP_COLOR 0x00FF0000
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

typedef struct s_win
{
    void    *mlx_ptr;
    void    *win_ptr;
}               t_win;

//are we allowed to use float?


typedef struct s_vector2
{
    float x;
    float y;
}               t_vector2;

typedef struct s_vector3
{
    float x;
    float y;
    float z;
}               t_vector3;

typedef struct s_map
{
    t_vector2       **map;
    int             maxX;
    int             maxY;
}               t_map;

typedef struct s_line
{
    t_vector3    p1;
    t_vector3    p2;
}            t_line;

int         ft_fdf(char *filename);
int         action_window(int keycode, t_win *win);
void        ft_draw_line(t_win *data, t_vector2 pos1, t_vector2 pos2);
int         ft_draw_map(t_win win, t_map *map);
void        ft_free_map(t_map *map);

t_map   *ft_get_map_from_file(int fd);
t_vector3   **ft_convert_map_to_vector3_map(int **map, int maxX, int maxY);

#endif
