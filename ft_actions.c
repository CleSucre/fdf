/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 07:26:35 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/22 07:26:35 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int action_window(int keycode, t_win *win)
{
    ft_printf("action_window keycode = %u\n", keycode);
    if (keycode == 65307)
    {
        mlx_destroy_window(win->mlx_ptr, win->win_ptr);
        exit(0);
    }
    return (0);
}
