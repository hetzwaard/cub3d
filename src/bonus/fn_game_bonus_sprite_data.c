/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_sprite_data.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:29:24 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 21:35:16 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_count_sprites(t_app *app)
{
	int		i;
	int		j;
	int		count;
	char	**map;

	map = app->map->map_2d;
	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'K')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	bonus_store_sprites(t_app *app, t_sprite *sprites)
{
	int		i;
	int		j;
	int		k;
	char	**map;

	map = app->map->map_2d;
	i = 0;
	k = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'K')
			{
				sprites[k].x = j + 0.5;
				sprites[k].y = i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
}

int	bonus_pitch_offset(t_game *g)
{
	double	ratio;

	ratio = g->player.pitch / GAME_PITCH_MAX;
	if (ratio > 1.0)
		ratio = 1.0;
	if (ratio < -1.0)
		ratio = -1.0;
	return ((int)(ratio * (g->render_h / 2)));
}

uint32_t	bonus_shade_color(uint32_t color, double shade)
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

uint32_t	bonus_sprite_color(t_game *g, char type)
{
	double	phase;
	double	pulse;

	(void)g;
	phase = mlx_get_time() * 4.0;
	pulse = (sin(phase) + 1.0) * 0.5;
	if (type == 'K')
		return (bonus_shade_color(KEY_COLOR, 0.7 + pulse * 0.3));
	return (bonus_shade_color(KEY_COLOR, 0.7 + pulse * 0.3));
}
