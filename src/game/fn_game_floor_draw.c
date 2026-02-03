/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_floor_draw.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:31:01 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:31:03 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_floor_fill(t_floor_draw *d, int y, uint32_t color, int step)
{
	int	i;

	i = 0;
	while (i < step && y + i < d->app->game->render_h)
	{
		d->col.buf[(y + i) * d->col.w + d->col.x] = color;
		i++;
	}
}

static void	game_floor_fast(t_floor_draw *d, t_bounds *b)
{
	int			y;

	y = b->end + 1;
	while (y < d->app->game->render_h)
	{
		game_floor_fill(d, y, (uint32_t)d->app->config->floor_rgb, d->step);
		y += d->step;
	}
}

static void	game_floor_slow(t_floor_draw *d, t_bounds *b, t_ray *ray)
{
	t_floor		f;
	int			y;
	uint32_t	color;
	int			step;
	int			limit;

	f.app = d->app;
	f.ray = ray;
	f.center = d->app->game->render_h / 2 + game_floor_pitch(d->app->game);
	f.cam_h = 0.5 + (d->app->game->player.z / 2.0);
	y = b->end + 1;
	limit = d->app->game->render_h / 3;
	while (y < d->app->game->render_h)
	{
		step = d->step;
		if (y < limit)
			step = 1;
		color = game_floor_color(&f, y);
		game_floor_fill(d, y, color, step);
		y += step;
	}
}

void	game_draw_floor(t_app *app, int x, t_bounds *b, t_ray *ray)
{
	t_floor_draw	d;

	d.app = app;
	d.col.buf = (uint32_t *)app->game->img->pixels;
	d.col.w = app->game->render_w;
	d.col.x = x;
	d.step = GAME_FLOOR_STEP;
	if (d.step < 1)
		d.step = 1;
	if (is_bonus_mode() == false)
		return (game_floor_fast(&d, b));
	if (app->map->has_lava == false)
		return (game_floor_fast(&d, b));
	game_floor_slow(&d, b, ray);
}
