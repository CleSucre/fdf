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

# include "../libft/include/libft.h"
# include "../libft/include/colors.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000
# define KEY_ESC 65307

typedef struct s_win
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*img_data;
	int					img_size;
	int					bpp;
	int					size_line;
}						t_win;

typedef struct s_vector2
{
	float				x;
	float				y;
}						t_vector2;

typedef struct s_vector3
{
	float				x;
	float				y;
	float				z;
}						t_vector3;

typedef struct s_line
{
	t_vector2			*point1;
	t_vector2			*point2;
	int					point1_color;
	int					point2_color;
}						t_line;

typedef struct s_camera
{
	t_vector3			position;
	float				yaw;
	float				pitch;
	float				fov;
}						t_camera;

typedef struct s_map
{
	t_vector3			**map_vector3;
	int					size_x;
	int					size_y;
	int					size_z;
	t_camera			*camera;
	t_vector3			*transformed_point1;
	t_vector3			*transformed_point2;
	t_line				*line;
	char				*text;
}						t_map;

typedef struct s_key_params
{
	t_win				*win;
	t_map				*map;
}						t_key_params;

void					ft_init_keymap(t_win *win, t_map *map);
t_map					*ft_get_map_from_file(int fd);

t_camera				*ft_init_camera(t_map *map);

int						ft_free_program(t_key_params *params);
void					*ft_free_map(t_map *map);

int						ft_get_color_between_two(int color1, int color2,
							float t);
int						ft_get_color_from_y(int y, int max_y, int min_y);

void					ft_draw_line(t_win *win, t_line *line);
void					ft_refresh_window(t_win *win, t_map *map);

void					ft_draw_map(t_map *map, t_win *win);

void					transform_point(t_vector3 *dst, t_vector3 *point,
							t_camera *camera);
void					ft_projet_vector3(t_vector2 *dst, t_vector3 *point,
							t_camera *camera);
int						ft_check_frustum(t_vector3 *transformed_point);

#endif
