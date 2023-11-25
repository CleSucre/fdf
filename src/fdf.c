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
    ft_printf("maxX = %d\nmaxY = %d\n", map->sizeX, map->sizeY);
    i = 0;
    while (lines[i] && i < map->sizeY)
    {
        positions = ft_split(lines[i], ' ');
        j = 0;
        while (positions[j] && j < map->sizeX)
        {
            tz = ft_atoi(positions[j]) + 1;
            map->map_vector3[i][j] = ft_make_vector3(j, tz, i);
            free(positions[j]);
            j++;
        }
        free(positions);
        free(lines[i]);
        i++;
    }
    free(lines);
    map->camera = ft_make_camera(ft_make_vector3(map->sizeX * 2, map->sizeY * 3, map->sizeX * 2), 7, 0.5, 100);
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
    mlx_hook(win->win_ptr, 2, 1L<<0, action_window, params);
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

    ft_draw_2d_map(map, &map->camera, &win);
    mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, win.img_ptr, 0, 0);

    mlx_loop(win.mlx_ptr);

    ft_free_map(map);
    mlx_destroy_window(win.mlx_ptr, win.win_ptr);
    free(win.mlx_ptr);
    free(win.win_ptr);
    free(win.img_ptr);
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
