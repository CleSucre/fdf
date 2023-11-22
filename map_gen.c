#include "fdf.h"

t_vector3   ft_get_vector3(int x, int y, int z)
{
    t_vector3   res;

    res.x = x;
    res.y = y;
    res.z = z;
    return (res);
}

void ft_free_vector3_map(t_vector3 **matrix, int maxY) {
    int i;

    i = 0;
    while (i < maxY)
        free(matrix[i++]);
    free(matrix);
}

void    ft_debug_vector3_matrix(t_vector3   **matrix, int maxX, int maxY) {
    int i;
    int j;

    (void)matrix;
    i = 0;
    while (i < maxX) {
        j = 0;
        while (j < maxY) {
            ft_printf("(%d, %d, %d) ", matrix[i][j].x, matrix[i][j].y, matrix[i][j].z);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}

t_vector3   **ft_convert_map_to_vector3_map(int **map, int maxX, int maxY)
{
    t_vector3 **res;
    int iy;
    int ix;

    res = (t_vector3 **)malloc(maxY * sizeof(t_vector3 *));
    if (res == NULL)
        return (NULL);
    iy = 0;
    while (iy < maxY) {
        res[iy] = (t_vector3 *)malloc(maxX * sizeof(t_vector3));
        if (res[iy] == NULL)
            return (NULL);
        ix = 0;
        while (ix < maxX) {
            res[iy][ix] = ft_get_vector3(ix, iy, map[iy][ix]);
            ix++;
        }
        iy++;
    }
    return (res);
}