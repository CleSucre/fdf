#include "fdf.h"

/**
 * @brief Get the color between two colors depending on t
 * @param color1
 * @param color2
 * @param t
 * @return int
 */
int	ft_get_color_between_two(int color1, int color2, float t)
{
	int	r;
	int	g;
	int	b;

	r = (int)((float)((color2 & 0xFF0000) >> 16) * t)
		+ (int)((float)((color1 & 0xFF0000) >> 16) * (1 - t));
	g = (int)((float)((color2 & 0x00FF00) >> 8) * t)
		+ (int)((float)((color1 & 0x00FF00) >> 8) * (1 - t));
	b = (int)((float)((color2 & 0x0000FF)) * t)
		+ (int)((float)((color1 & 0x0000FF)) * (1 - t));
	return ((r << 16) + (g << 8) + b);
}

/**
 * @brief Get the color from the y coordinate
 * @param y
 * @return int
 */
int	ft_get_color_from_y(int y, int max_y, int min_y)
{
	if (y < min_y)
		return (HEX_BLUE);
	if (y > max_y)
		return (HEX_RED);
	return (ft_get_color_between_two(HEX_BLUE, HEX_RED, (float)(y - min_y)
			/ (float)(max_y - min_y)));
}
