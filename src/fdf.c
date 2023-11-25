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

static t_map   *ft_get_map_from_file(int fd)
{
    t_map       *map;
    char        **lines;
    char        **positions;
    int         i;
    int         j;
    float       tz;

    lines = get_lines(fd);
    if (lines == NULL)
        return (NULL);
    i = 0;
    while (lines[i])
    {
        ft_printf("%s\n", lines[i]);
        i++;
    }
    map = ft_init_map(ft_count_words(lines[0], ' '), i);
    i = 0;
    while (lines[i] && i < map->sizeZ)
    {
        positions = ft_split(lines[i], ' ');
        j = 0;
        while (positions[j] && j < map->sizeX)
        {
            tz = ft_atoi(positions[j]) + 1;
            map->map_vector3[i][j] = ft_make_vector3(j, tz, i);
            if (tz > map->sizeY)
                map->sizeY = tz;
            free(positions[j]);
            j++;
        }
        free(positions);
        free(lines[i]);
        i++;
    }
    free(lines);
    ft_printf("maxX = %d\nmaxY = %d\nmaxZ = %d\n", map->sizeX, map->sizeY, map->sizeZ);
    //place camera above the map facing up
    map->camera = ft_init_camera(ft_make_vector3(map->sizeX * 2, map->sizeY * 3, map->sizeZ * 3));
    //map->sizeX * 2, map->sizeY, map->sizeZ * 2), 7, 0.5, 100);
    map->refresh_window = ft_refresh_window;
    return (map);
}

static t_win  ft_init_window(char *filename)
{
    t_win win;

    win.mlx_ptr = mlx_init();
    win.win_ptr = mlx_new_window(win.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, filename);
    win.img_ptr = mlx_new_image(win.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    return (win);
}

void    ft_init_keymap(t_win *win, t_map *map)
{
    t_key_params    *params;

    params = (t_key_params*)malloc(sizeof(t_key_params));
    if (params == NULL)
    {
        ft_printf("malloc error in ft_init_keymap\n");
        exit(0);
    }
    params->win = win;
    params->map = map;

    mlx_do_key_autorepeaton(win->mlx_ptr);
    mlx_mouse_hook(win->win_ptr, action_mouse_key, params);
    mlx_hook(win->win_ptr, 5, BUTTON_RELEASE_MASK, action_mouse_key, params);

    mlx_hook(win->win_ptr, 2, KEY_PRESS_MASK, action_key, params);
    mlx_hook(win->win_ptr, 6, POINTER_MOTION_MASK, action_mouse_move, params);
    mlx_hook(win->win_ptr, 17, STRUCTURE_NOTIFY_MASK, ft_free_program, params);
}

int    ft_free_program(t_key_params *params)
{
    //mlx_destroy_window(params->win->mlx_ptr, params->win->win_ptr);
    ft_free_map(params->map);
    //free(params->win->mlx_ptr);
    //free(params->win->win_ptr);
    //free(params->win->img_ptr);
    //free(params);
    exit(0);
}

static int    ft_fdf(char *filename)
{
    t_map       *map;
    int         fd;
    t_win       win;

    fd = open(filename, O_RDONLY);
    map = ft_get_map_from_file(fd);
    close(fd);
    if (map == NULL)
        return (1);

    win = ft_init_window(filename);
    ft_init_keymap(&win, map);

    ft_draw_2d_map(map, map->camera, &win);
    mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, win.img_ptr, 0, 0);

    mlx_loop(win.mlx_ptr);

    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("usage: ./fdf <filename>\n");
        return (0);
    }
    return (ft_fdf(argv[1]));
}
