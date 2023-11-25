#include "fdf.h"

/**
 * @brief Converts a 3D point to a 2D point.
 *
 * @param point Point to convert.
 * @param camera Camera information.
 * @return t_vector2 Converted point.
 */
static t_vector2 ft_3d_to_2d(t_vector3 point, t_camera *camera) {
    // Translation of the point relative to the camera position
    point.x -= camera->pos.x;
    point.y -= camera->pos.y;
    point.z -= camera->pos.z;

    // Rotation of the point around the x, y axes
    float cosYaw = cosf(camera->yaw);
    float sinYaw = sinf(camera->yaw);
    float cosPitch = cosf(camera->pitch);
    float sinPitch = sinf(camera->pitch);

    float newX = point.x * cosYaw - point.z * sinYaw;
    float newZ = point.x * sinYaw + point.z * cosYaw;
    point.x = newX;
    point.z = newZ;

    float newY = point.y * cosPitch - point.z * sinPitch;
    float newZ2 = point.y * sinPitch + point.z * cosPitch;
    point.y = newY;
    point.z = newZ2;

    // Projection of the point on the 2D plane
    float distance = point.z;
    point.x /= distance;
    point.y /= distance;

    // Application of the field of view (fov)
    float screenDistance = tanf(camera->fov * 0.5f);
    point.x /= screenDistance;
    point.y /= screenDistance;

    t_vector2 projectedPoint;

    // Mapping of 2D coordinates to the screen
    projectedPoint.x = (point.x + 1.0f) * 0.5f * SCREEN_WIDTH;
    projectedPoint.y = (1.0f - point.y) * 0.5f * SCREEN_HEIGHT;
    return (projectedPoint);
}
/**
 * @brief Draws a line between two points in a 2D window.
 *
 * @param map Environment information.
 * @param camera Camera information.
 */
void    ft_draw_2d_map(t_map *map, t_camera *camera, t_win *win)
{
    int i;
    int j;
    t_vector2 *point1;
    t_vector2 *point2;

    point1 = (t_vector2 *)malloc(sizeof(t_vector2));
    if (point1 == NULL)
        return ;
    point2 = (t_vector2 *)malloc(sizeof(t_vector2));
    if (point2 == NULL)
    {
        free(point1);
        return ;
    }
    i = 0;
    while (i < map->sizeZ)
    {
        j = 0;
        while (j < map->sizeX)
        {
            if (j + 1 < map->sizeX)
            {
                *point1 = ft_3d_to_2d(map->map_vector3[i][j], camera);
                *point2 = ft_3d_to_2d(map->map_vector3[i][j + 1], camera);
                ft_draw_line(
                    win,
                    ft_make_line(*point1, *point2,
                        ft_get_color_from_y(map->map_vector3[i][j].y, map->sizeY, 0),
                        ft_get_color_from_y(map->map_vector3[i][j + 1].y, map->sizeY, 0)
                    )
                );
            }
            if (i + 1 < map->sizeZ)
            {
                *point1 = ft_3d_to_2d(map->map_vector3[i][j], camera);
                *point2 = ft_3d_to_2d(map->map_vector3[i + 1][j], camera);
                ft_draw_line(
                    win,
                    ft_make_line(*point1, *point2,
                     ft_get_color_from_y(map->map_vector3[i][j].y, map->sizeY, 0),
                     ft_get_color_from_y(map->map_vector3[i + 1][j].y, map->sizeY, 0)
                    )
                );
            }
            j++;
        }
        i++;
    }
    free(point1);
    free(point2);
}
