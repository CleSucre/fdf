/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:56:17 by julthoma          #+#    #+#             */
/*   Updated: 2024/05/01 02:09:13 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_get_color_between_two(int color1, int color2, float t)
{
	int	r;
	int	g;
	int	b;

	r = (int)((float)((color2 & 0xFF0000) >> 16) *t)
		+ (int)((float)((color1 & 0xFF0000) >> 16) *(1 - t));
	g = (int)((float)((color2 & 0x00FF00) >> 8) *t)
		+ (int)((float)((color1 & 0x00FF00) >> 8) *(1 - t));
	b = (int)((float)((color2 & 0x0000FF)) *t)
		+ (int)((float)((color1 & 0x0000FF)) *(1 - t));
	return ((r << 16) + (g << 8) + b);
}

int	ft_get_color_from_y(int y, int max_y, int min_y)
{
	if (y < min_y)
		return (HEX_BLUE);
	if (y > max_y)
		return (HEX_RED);
	return (ft_get_color_between_two(HEX_BLUE, HEX_GREEN, (float)(y - min_y)
		/ (float)(max_y - min_y)));
}
