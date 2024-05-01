/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:17:11 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 02:09:25 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	ft_create_image(win);
	ft_refresh_window(win, map);
	mlx_loop(win->mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("usage: ./fdf <filename>\n");
		return (0);
	}
	return (ft_fdf(argv[1]));
}
