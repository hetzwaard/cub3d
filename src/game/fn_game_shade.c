/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_shade.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:32:43 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:32:45 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	game_shade_factor(t_ray *ray)
{
	double	shade;

	shade = 1.0 / (1.0 + ray->dist * 0.12);
	if (ray->side == 1)
		shade *= 0.85;
	if (shade < 0.15)
		shade = 0.15;
	return (shade);
}

uint32_t	game_shade_color(uint32_t color, double shade)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	r = (uint32_t)(r * shade);
	g = (uint32_t)(g * shade);
	b = (uint32_t)(b * shade);
	return (r << 24 | g << 16 | b << 8 | a);
}
