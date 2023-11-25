#include "fdf.h"

/**
 * @brief Checks if a point is in the frustum of the camera, and returns its 2D coordinates if it is.
 *
 * @param point Point to check.
 * @param camera Camera information.
 * @return t_vector2* Returns the point in 2D if it is in the frustum, NULL otherwise.
 */
static t_vector2 *ft_is_in_frustum(t_vector3 point, t_camera *camera) {
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

    t_vector2 *projectedPoint;
    projectedPoint = (t_vector2 *)malloc(sizeof(t_vector2));
    if (projectedPoint == NULL)
        return (NULL);

    // Check if the point is within the normalized device coordinates
    if (fabs(point.x) <= 1.0f && fabs(point.y) <= 1.0f) {
        // Mapping of 2D coordinates to the screen
        projectedPoint->x = (point.x + 1.0f) * 0.5f * SCREEN_WIDTH;
        projectedPoint->y = (1.0f - point.y) * 0.5f * SCREEN_HEIGHT;
        return (projectedPoint);
    }
    return (NULL);
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

    i = 0;
    while (i < map->sizeY)
    {
        j = 0;
        while (j < map->sizeX)
        {
            if (j + 1 < map->sizeX)
            {
                point1 = ft_is_in_frustum(map->map_vector3[i][j], camera);
                if (point1)
                {
                    point2 = ft_is_in_frustum(map->map_vector3[i][j + 1], camera);
                    if (point2)
                    {
                        ft_draw_line(win, *point1, *point2);
                        free(point2);
                    }
                    free(point1);
                }
            }
            if (i + 1 < map->sizeY)
            {
                point1 = ft_is_in_frustum(map->map_vector3[i][j], camera);
                if (point1)
                {
                    point2 = ft_is_in_frustum(map->map_vector3[i + 1][j], camera);
                    if (point2)
                    {
                        ft_draw_line(win, *point1, *point2);
                        free(point2);
                    }
                    free(point1);
                }
            }
            j++;
        }
        i++;
    }
}
