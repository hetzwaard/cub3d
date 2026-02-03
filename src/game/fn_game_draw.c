/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_draw.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:30:54 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:30:55 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_fill_column(t_column *col, int y_start,
		int y_end, uint32_t color)
{
	int	y;

	if (y_start > y_end)
		return ;
	y = y_start;
	while (y <= y_end)
	{
		col->buf[y * col->w + col->x] = color;
		y++;
	}
}

static int	game_pitch_offset(t_game *game)
{
	double	ratio;

	ratio = game->player.pitch / GAME_PITCH_MAX;
	if (ratio > 1.0)
		ratio = 1.0;
	if (ratio < -1.0)
		ratio = -1.0;
	return ((int)(ratio * (game->render_h / 2)));
}

static void	game_set_bounds(t_game *g, double dist, double wall_h,
		t_wall_bounds *wb)
{
	int	pitch;
	int	zshift;

	wb->line_h = (int)((g->render_h * wall_h) / dist);
	pitch = game_pitch_offset(g);
	zshift = (int)(g->player.z * (wb->line_h / 2.0));
	wb->center = g->render_h / 2 + pitch + zshift;
	wb->b.start = -(wb->line_h) / 2 + wb->center;
	wb->b.end = (wb->line_h) / 2 + wb->center;
	if (wb->b.start < 0)
		wb->b.start = 0;
	if (wb->b.end >= g->render_h)
		wb->b.end = g->render_h - 1;
}

void	game_draw_column(t_app *app, int x, t_ray *ray)
{
	t_game		*g;
	t_wall_draw	w;
	double		wall_h;

	g = app->game;
	w.col.buf = (uint32_t *)g->img->pixels;
	w.col.w = g->render_w;
	w.col.x = x;
	wall_h = 1.0;
	game_set_bounds(g, ray->dist, wall_h, &w.wb);
	game_fill_column(&w.col, 0, w.wb.b.start - 1,
		(uint32_t)app->config->ceil_rgb);
	game_draw_wall(&w, app, ray);
	game_draw_floor(app, x, &w.wb.b, ray);
}
