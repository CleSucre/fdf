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

# include "../libft/include/colors.h"
# include "../libft/include/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>

# define MAP_COLOR HEX_BLUE
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

typedef struct s_win
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
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
	t_vector2			point1;
	t_vector2			point2;
	int					point1_color;
	int					point2_color;
}						t_line;

typedef struct s_mouse_info
{
	t_vector2			pos;
	t_vector2			last_pos;
	t_vector2			pos_on_lock;
	int					lock;
}						t_mouse_info;

typedef struct s_camera
{
	t_vector3			pos;
	float				yaw;
	float				pitch;
	float				fov;
	float				near;
	float				far;
	t_mouse_info		*mouse;
}						t_camera;

struct			s_map;

typedef void	(*t_function_pointer)(struct s_win *, struct s_map *);

typedef struct s_map
{
	t_vector3			**map_vector3;
	int					size_x;
	int					size_y;
	int					size_z;
	t_camera			*camera;
	t_function_pointer	refresh_window;
}						t_map;

typedef struct s_key_params
{
	t_win				*win;
	t_map				*map;
}						t_key_params;

int						action_key(int keycode, t_key_params *params);
int						action_mouse_key(int button, int x, int y,
							void *params);
int						action_mouse_move(int x, int y, void *params);
int						ft_free_program(t_key_params *params);
t_map					*ft_get_map_from_file(int fd);

t_vector2				ft_3dto2d(t_vector3 point, t_camera *camera,
							int screenWidth, int screenHeight);

t_vector3				ft_make_vector3(float x, float y, float z);
t_camera				*ft_init_camera(t_vector3 pos);
t_line					ft_make_line(t_vector2 point1, t_vector2 point2,
							int point1_color, int point2_color);
t_map					*ft_init_map(int maxX, int maxZ);
void					*ft_free_map(t_map *map);

int						ft_get_color_between_two(int color1, int color2,
							float t);
int						ft_get_color_from_y(int y, int max_y, int min_y);
void					ft_draw_line(t_win *win, t_line line);
void					ft_convert_to_map_vector2(t_map *map);
void					ft_refresh_window(t_win *win, t_map *map);

void					ft_debug_vector2(t_vector2 vector2);
void					ft_debug_vector3(t_vector3 vector3);
void					ft_debug_map(t_map *map);

void					ft_draw_2d_map(t_map *map, t_camera *camera, t_win *win);

t_vector2				ft_3d_to_2d(t_vector3 point, t_camera *camera);

#endif
