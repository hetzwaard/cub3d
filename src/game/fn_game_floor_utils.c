/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_floor_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:31:06 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:31:08 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	game_is_lava(t_app *app, double x, double y)
{
	int	mx;
	int	my;

	if (x < 0.0 || y < 0.0)
		return (false);
	mx = (int)x;
	my = (int)y;
	if (my < 0 || my >= app->map->height || mx < 0)
		return (false);
	if (app->map->row_len && mx >= app->map->row_len[my])
		return (false);
	if (app->map->map_2d[my] && app->map->map_2d[my][mx] == 'L')
		return (true);
	return (false);
}

static double	game_floor_shade(double dist)
{
	double	shade;

	shade = 1.0 / (1.0 + dist * 0.12);
	if (shade < 0.15)
		shade = 0.15;
	return (shade);
}

int	game_floor_pitch(t_game *g)
{
	double	ratio;

	ratio = g->player.pitch / GAME_PITCH_MAX;
	if (ratio > 1.0)
		ratio = 1.0;
	if (ratio < -1.0)
		ratio = -1.0;
	return ((int)(ratio * (g->render_h / 2)));
}

double	game_plane_dist(t_floor *f, double plane_h, int y)
{
	double	d;

	d = (double)(y - f->center);
	if (d <= 0.0)
		return (-1.0);
	return ((f->cam_h - plane_h) * f->app->game->render_h / d);
}

uint32_t	game_floor_color(t_floor *f, int y)
{
	double	dist;
	double	fx;
	double	fy;

	dist = game_plane_dist(f, GAME_LAVA_Z, y);
	if (dist > 0.0)
	{
		fx = f->app->game->player.x + dist * f->ray->dir_x;
		fy = f->app->game->player.y + dist * f->ray->dir_y;
		if (game_is_lava(f->app, fx, fy))
			return (game_shade_color(GAME_LAVA_COLOR, game_floor_shade(dist)));
	}
	return ((uint32_t)f->app->config->floor_rgb);
}
