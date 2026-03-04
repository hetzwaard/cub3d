/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fn_game_bonus_keys.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/30 17:26:10 by mahkilic      #+#    #+#                 */
/*   Updated: 2026/02/02 16:25:42 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	bonus_key_color(xpm_t *xpm, int x, int y)
{
	uint8_t	*p;

	p = &xpm->texture.pixels[(y * xpm->texture.width + x) * 4];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static int	bonus_row_len(t_app *app, int y)
{
	if (app->map->row_len)
		return (app->map->row_len[y]);
	return ((int)ft_strlen(app->map->map_2d[y]));
}

static void	bonus_try_set_checkpoint(t_app *app, int key_x, int key_y)
{
	t_game		*g;
	double		best_dist;
	double		dist_x;
	double		dist_y;
	double		dist;
	int			x;
	int			y;

	g = app->game;
	best_dist = HUGE_DIST;
	y = -1;
	while (++y < app->map->height)
	{
		if (app->map->map_2d[y] == NULL)
			continue ;
		x = -1;
		while (++x < bonus_row_len(app, y))
		{
			if (app->map->map_2d[y][x] != 'C')
				continue ;
			dist_x = ((double)x + 0.5) - ((double)key_x + 0.5);
			dist_y = ((double)y + 0.5) - ((double)key_y + 0.5);
			dist = dist_x * dist_x + dist_y * dist_y;
			if (dist < best_dist)
			{
				best_dist = dist;
				g->respawn_x = (double)x + 0.5;
				g->respawn_y = (double)y + 0.5;
			}
		}
	}
	if (best_dist < HUGE_DIST)
		g->checkpoint_armed = true;
}

void	bonus_update_keys(t_app *app)
{
	t_player	*p;
	t_game		*g;
	int			mx;
	int			my;

	if (app == NULL || app->game == NULL || is_bonus_mode() == false)
		return ;
	g = app->game;
	p = &app->game->player;
	if (p->x < 0.0 || p->y < 0.0)
		return ;
	mx = (int)p->x;
	my = (int)p->y;
	if (my < 0 || my >= app->map->height || mx < 0)
		return ;
	if (app->map->row_len && mx >= app->map->row_len[my])
		return ;
	if (app->map->map_2d[my] && app->map->map_2d[my][mx] == 'K')
	{
		app->map->map_2d[my][mx] = '0';
		g->keys++;
		bonus_try_set_checkpoint(app, mx, my);
	}
}

static void	bonus_draw_key_icon(t_game *g, int x, int y, double shade)
{
	xpm_t		*xpm;
	int			i;
	int			j;
	uint32_t	color;

	xpm = g->key_xpm;
	if (xpm == NULL)
		return ;
	i = 0;
	while (i < (int)xpm->texture.height)
	{
		j = 0;
		while (j < (int)xpm->texture.width)
		{
			color = bonus_key_color(xpm, j, i);
			if ((color & 0xFF) != 0)
				bonus_put_pixel(g, x + j, y + i,
					bonus_shade_color(color, shade));
			j++;
		}
		i++;
	}
}

static void	bonus_hud_setup(t_game *g, t_hud *hud)
{
	hud->count = g->keys;
	hud->shade = 1.0;
	if (hud->count < 1)
	{
		hud->count = 1;
		hud->shade = 0.35;
	}
	hud->step = (int)g->key_xpm->texture.width + 4;
	hud->x = g->render_w - 16 - hud->count * hud->step;
	if (hud->x < 0)
		hud->x = 0;
}

void	bonus_render_hud(t_app *app)
{
	t_game	*g;
	t_hud	hud;
	int		i;

	g = app->game;
	if (g == NULL || is_bonus_mode() == false || g->key_xpm == NULL)
		return ;
	bonus_hud_setup(g, &hud);
	i = 0;
	while (i < hud.count)
	{
		bonus_draw_key_icon(g, hud.x, 16, hud.shade);
		hud.x += hud.step;
		i++;
	}
}
