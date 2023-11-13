/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:35:18 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/13 09:35:18 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_data  ft_init_window(char *filename)
{
    t_data data;

    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 500, filename);
    return (data);
}

int    ft_fdf(char *filename)
{
    t_data  data;
    t_vector2  pos1;
    t_vector2  pos2;

    data = ft_init_window(filename);
    mlx_key_hook(data.win_ptr, action_window, &data);

    pos1.x = 200;
    pos1.y = 200;

    pos2.x = 100;
    pos2.y = 300;
    
    ft_draw_line(&data, &pos1, &pos2);
    mlx_loop(data.mlx_ptr);
    free(data.mlx_ptr);
    free(data.win_ptr);
    return (0);
}