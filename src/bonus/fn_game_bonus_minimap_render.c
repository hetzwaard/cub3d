/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_minimap_render.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 16:29:03 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:29:34 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bonus_minimap_state(t_game *g, t_minimap *m)
{
	double	fx;
	double	fy;

	m->start_x = (int)floor(g->player.x) - MINI_RADIUS;
	m->start_y = (int)floor(g->player.y) - MINI_RADIUS;
	fx = g->player.x - floor(g->player.x);
	fy = g->player.y - floor(g->player.y);
	m->off_x = (int)((fx - 0.5) * MINI_TILE);
	m->off_y = (int)((fy - 0.5) * MINI_TILE);
}

static void	bonus_draw_minimap_row(t_app *app, int my, t_minimap *m,
		t_rect box)
{
	t_game	*g;
	int		mx;
	t_rect	rect;
	char	cell;

	g = app->game;
	mx = -1;
	while (mx <= MINI_RADIUS * 2 + 1)
	{
		rect.x = MINI_MARGIN + mx * MINI_TILE - m->off_x;
		rect.y = MINI_MARGIN + my * MINI_TILE - m->off_y;
		rect.w = MINI_TILE;
		rect.h = MINI_TILE;
		cell = bonus_cell_at(app, m->start_x + mx, m->start_y + my);
		bonus_fill_rect_clipped(g, rect, box, bonus_minimap_color(cell));
		mx++;
	}
}

static void	bonus_draw_border(t_game *g, t_rect box)
{
	bonus_fill_rect_color(g, (t_rect){box.x, box.y,
		box.w, 1}, MINI_WALL);
	bonus_fill_rect_color(g, (t_rect){box.x, box.y + box.h - 1,
		box.w, 1}, MINI_WALL);
	bonus_fill_rect_color(g, (t_rect){box.x, box.y,
		1, box.h}, MINI_WALL);
	bonus_fill_rect_color(g, (t_rect){box.x + box.w - 1, box.y,
		1, box.h}, MINI_WALL);
}

void	bonus_render_minimap(t_app *app)
{
	int			my;
	t_game		*g;
	t_minimap	m;
	t_rect		box;

	g = app->game;
	if (g->minimap_enabled == false)
		return ;
	bonus_minimap_state(g, &m);
	box = (t_rect){MINI_MARGIN, MINI_MARGIN,
		MINI_TILE * (MINI_RADIUS * 2 + 1),
		MINI_TILE * (MINI_RADIUS * 2 + 1)};
	my = -1;
	while (my <= MINI_RADIUS * 2 + 1)
	{
		bonus_draw_minimap_row(app, my, &m, box);
		my++;
	}
	bonus_draw_fov(app);
	bonus_draw_border(g, box);
	bonus_fill_rect_color(g, (t_rect){box.x + MINI_RADIUS * MINI_TILE
		+ MINI_TILE / 2 - 1, box.y + MINI_RADIUS * MINI_TILE
		+ MINI_TILE / 2 - 1, 3, 3}, MINI_PLAYER);
}
