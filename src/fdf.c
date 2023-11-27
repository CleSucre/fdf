/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 06:42:21 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/13 06:42:21 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "key_map.h"

/**
 * @brief Initialize the window
 * @param filename used to name the window
 * @return t_win
 */
static t_win	*ft_init_window(char *filename)
{
	t_win	*win;

	win = (t_win *)malloc(sizeof(t_win));
	if (win == NULL)
	{
		ft_printf("malloc error in ft_init_window\n");
		exit(0);
	}
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
			filename);
	win->img_ptr = mlx_new_image(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	return (win);
}

/**
 * @brief Initialize the keymap
 * @param win
 * @param map
 */
void	ft_init_keymap(t_win *win, t_map *map)
{
	t_key_params	*params;

	params = (t_key_params *)malloc(sizeof(t_key_params));
	if (params == NULL)
	{
		ft_printf("malloc error in ft_init_keymap\n");
		exit(0);
	}
	params->win = win;
	params->map = map;
	mlx_do_key_autorepeaton(win->mlx_ptr);
	mlx_mouse_hook(win->win_ptr, action_mouse_key, params);
	mlx_hook(win->win_ptr, 5, 1L << 3, action_mouse_key, params);
	mlx_hook(win->win_ptr, 2, 1L << 0, action_key, params);
	mlx_hook(win->win_ptr, 6, 1L << 6, action_mouse_move, params);
	mlx_hook(win->win_ptr, 17, 1L << 17, ft_free_program, params);
}

/**
 * @brief Free the program
 * @param params
 * @return int
 */
int	ft_free_program(t_key_params *params)
{
	// mlx_destroy_window(params->win->mlx_ptr, params->win->win_ptr);
	ft_free_map(params->map);
	free(params->win->mlx_ptr);
	free(params->win->win_ptr);
	free(params->win->img_ptr);
	free(params);
	exit(0);
}

/**
 * @brief Main function
 * @param filename
 * @return int
 */
static int	ft_fdf(char *filename)
{
	t_map	*map;
	int		fd;
	t_win	*win;

	fd = open(filename, O_RDONLY);
	map = ft_get_map_from_file(fd);
	close(fd);
	if (map == NULL)
		return (1);
	win = ft_init_window(filename);
	ft_init_keymap(win, map);
	ft_draw_2d_map(map, map->camera, win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	mlx_loop(win->mlx_ptr);
	return (0);
}

/**
 * @brief Main function
 * @param argc
 * @param argv
 * @return int
 */
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("usage: ./fdf <filename>\n");
		return (0);
	}
	return (ft_fdf(argv[1]));
}
