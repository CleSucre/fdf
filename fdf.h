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

# define MAP_COLOR 0x00FF0000

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
}               t_data;

typedef struct s_vector2
{
    int x;
    int y;
}               t_vector2;

typedef struct s_vector3
{
    int x;
    int y;
    int z;
}               t_vector3;

typedef struct s_line
{
    t_vector3    p1;
    t_vector3    p2;
}            t_line;

int     ft_fdf(char *filename);
int     action_window(int keycode, t_data *data);
void    ft_draw_line(t_data *data, t_vector2 *pos1, t_vector2 *pos2);

#endif
