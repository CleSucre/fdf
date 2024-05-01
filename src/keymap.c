/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:51:50 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 06:53:26 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	action_key(int keycode, t_key_params *params)
{
	if (keycode == KEY_ESC)
	{
		ft_free_program(params);
		return (1);
	}
	return (0);
}

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
	mlx_hook(win->win_ptr, 2, 1L << 0, action_key, params);
	mlx_hook(win->win_ptr, 17, 1L << 17, ft_free_program, params);
}
